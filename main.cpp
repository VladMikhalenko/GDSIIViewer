#include "mainwindow.h"
#include <QApplication>
#include "inc/LithographyTools/GaussianKernel.h"
#include <memory>
#include <iomanip>
#include "inc/LithographyTools/LineAnalyzer.h"
#include "inc/GUI/GDSIILineContainer.h"
#include "utils/Encoder/GDSIIDesignEncoder.h"
#include <fstream>

//функци распределения значений цвета на промежутке y1 y2
double FindYCoordT(double x1,double y1, double x2,double y2,double x)
{
    return static_cast<double>((-1)*(((y2-y1)*x+x1*(y1-y2)+y1*(x2-x1)))/(double)(x1-x2)+0.5);
}

double FindXCoordT(double x1,double y1, double x2,double y2,double y)
{
    return ((-1)*((x1-x2)*y+x1*(y1-y2)+y1*(x2-x1)))/(y2-y1);
}

void ShootColorRay(QImage &img,QPoint point,kernel_type kernel)
{
    int hSize=kernel.size()/2;
    int initX=point.x()-hSize;
    int initY=point.y()-hSize;

    for(int x=initX, kx=0;x<point.x()+hSize;x++,kx++)
    {
        if(x<0 || x>img.width()-1) continue;
        for(int y=initY,ky=0;y<point.y()+hSize;y++,ky++)
        {
            if(y<0 || y>img.height()-1) continue;

            int RED=255;
            int GREEN=255,BLUE=0;
            double BOTTOM=0.0,MIDDLE=0.5,MAX=1.0;

            double kIntens=kernel[kx][ky];//kernel weight

            QColor pixCol=img.pixel(x,y);
            int _pr=pixCol.red();
            int _pg=pixCol.green();
            int _pb=pixCol.blue();
            //вес зеленого текущем пикселе
            double gIntens=FindXCoordT(MIDDLE,BOTTOM,MAX,255.0,pixCol.green());
            //интерпретация веса зеленого: если пискель имеет красно-зеленый оттенок,
            //то коэфициент рассматривается без изменений, иначе находим значение равное разнице 1 и веса
            double greenInterpret=(_pr==255 && _pg>0 && _pb==0)?gIntens:1.0-gIntens;

            double newIntensityCoef=greenInterpret+kIntens<1.0?greenInterpret+kIntens:0.99;
            if(pixCol.green()<20 && pixCol.red()<20 && pixCol.blue()<20)
            {
                //if selected pixel color is close to black, then we don't change it's color
                RED=pixCol.red();
                GREEN=pixCol.green();
                BLUE=pixCol.blue();
            }
            else
            {
                if(newIntensityCoef>=0.5)
                {
                    GREEN=FindYCoordT(MIDDLE,BOTTOM,MAX,255.0,newIntensityCoef);
                    BLUE=0;
                }
                else if(newIntensityCoef>0)
                {
                    GREEN=BLUE=GREEN-FindYCoordT(BOTTOM,BOTTOM,MIDDLE,255.0,newIntensityCoef);
                }
            }
            img.setPixelColor(x,y,QColor(RED,GREEN,BLUE));//r-variable, g,b - constant,
        }
    }
}

void ShootBlackRayT(QImage &img,QPoint point,kernel_type kernel)
{
    int hSize=kernel.size()/2;
    int initX=point.x()-hSize;
    int initY=point.y()-hSize;

    for(int x=initX, kx=0;x<point.x()+hSize;x++,kx++)
    {
        if(x<0 || x>img.width()-1) continue;
        for(int y=initY,ky=0;y<point.y()+hSize;y++,ky++)
        {
            if(y<0 || y>img.height()-1) continue;

            int newColor=255;
            double BOTTOM=0.0,MAX=0.45;

            double kIntens=kernel[kx][ky];//kernel weight

            QColor pixCol=img.pixel(x,y);
            int _pg=pixCol.green();

            //функция зависимости значения цвета от интенсивности описывается линейной функцией(уравнение прямой):
            //в 0 цвет равен 255, в 1.0 цвет равен 0
            double blackInt=FindXCoordT(BOTTOM,MAX*255,MAX,0,_pg);

            double newIntensityCoef=blackInt+kIntens<MAX?blackInt+kIntens:MAX-0.01;//blackInt+kIntens<1.0?blackInt+kIntens:0.99;
            newColor=static_cast<int>(FindYCoordT(BOTTOM,255.0*MAX,MAX,0.0,newIntensityCoef));
            img.setPixelColor(x,y,QColor(newColor,newColor,newColor));//r-variable, g,b - constant,
        }
    }
}

void CodePrinter(CodeType code)
{
    switch (code) {
    case ERROR_CODE:
        std::cout<<"ERROR_CODE"<<std::endl;
        break;
    case EMPTY:
        std::cout<<"EPMTY"<<std::endl;
        break;
    case HORIZO_CODE:
        std::cout<<"HORIZ"<<std::endl;
        break;
    case VERTIC_CODE:
        std::cout<<"VERTI"<<std::endl;
        break;
    case R_UP_CORNER:
        std::cout<<"RUP"<<std::endl;
        break;
    case L_UP_CORNER:
        std::cout<<"LUP"<<std::endl;
        break;
    case R_LW_CORNER:
        std::cout<<"RLW"<<std::endl;
        break;
    case L_LW_CORNER:
        std::cout<<"LLW"<<std::endl;
        break;
    default:
        break;
    }
}
void ContainerPrinter(GDSIILineContainer &cont)
{
    for(GDSIILine l:cont.GetArray())
    {
        std::cout<<"("<<l.GetP1().GetX()<<","<<l.GetP1().GetY()<<"|"<<l.GetP2().GetX()<<","<<l.GetP2().GetY()<<")"<<std::endl;
    }
}
void MapPrinter(const std::map<int,int>& map)
{
    auto it = map.begin();
    if(it != map.end())
    {
        while(it != map.end())
        {
            std::cout<<"x:["<<it->first
                <<"]\n\tstart pos:["<<DECODE_LEFT_IN_INT32(it->second)
                <<"]\n\tpoint num:["<<DECODE_RIGHT_IN_INT32(it->second)
                <<"]\n";
            ++it;
        }
    }
}

int RunMAIN(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
    QCoreApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

int RunTEST1()
{
    GDSIILine a(15,15,15,25);
    GDSIILine b(15,25,25,25);
    GDSIILine c(25,25,25,15);
    GDSIILine d(25,15,15,15);

    GDSIILine e(0,0,0,40);
    GDSIILine f(0,40,40,40);
    GDSIILine g(40,40,40,0);
    GDSIILine h(40,0,0,0);

    GDSIILineContainer cont;
    cont.AddLine(b);
    cont.AddLine(c);
    cont.AddLine(a);
    cont.AddLine(d);
    cont.AddLine(e);
    cont.AddLine(f);
    cont.AddLine(g);
    cont.AddLine(h);
    ContainerPrinter(cont);
    std::cout<<"|-------------------TEST-------------------|"<<std::endl;
    GDSIIDesignEncoder::GetInstance().Encode(cont,10);
    std::cout<<"|-------------------||||-------------------|"<<std::endl;
    return 0;
}
int RunDiag2()
{
    GDSIILine a(0,0,60,60);
    GDSIILineContainer cont;
    cont.AddLine(a);
    GDSIIDesignEncoder::GetInstance().Encode(cont,10);
    return 0;
}
int Run3LineTest()
{
    //s code
    GDSIILine s1(15,15,15,25);
    GDSIILine s2( 5,15,15,15);
    GDSIILine s3(15,25,30,25);
    //z code
    GDSIILine z1(15,15,15,25);
    GDSIILine z2( 5,25,15,25);
    GDSIILine z3(15,15,30,15);
    //s rotated
    GDSIILine s4(15,15,15,25);
    GDSIILine s5( 5,25,15,25);
    GDSIILine s6( 5,25, 5,35);
    //z rotated
    GDSIILine z4( 5,15, 5,25);
    GDSIILine z5( 5,25,15,25);
    GDSIILine z6(15,25,15,35);


    LineAnalyzer analys;
    std::cout<<"S(9)="<<analys.GetCode(s1,s2,s3)<<std::endl;
    std::cout<<"Z(7)="<<analys.GetCode(z1,z2,z3)<<std::endl;
    std::cout<<"SR(10)="<<analys.GetCode(s4,s5,s6)<<std::endl;
    std::cout<<"ZR(8)="<<analys.GetCode(z4,z5,z6)<<std::endl;
    return 0;
}
int largeTest()
{
    GDSIILine a1(10,75,10,95);
    GDSIILine a2(10,95,65,95);
    GDSIILine a3(65,95,65,75);
    GDSIILine a4(65,75,10,75);

    GDSIILine b1(75,85,75,95);
    GDSIILine b2(75,95,115,95);
    GDSIILine b3(115,95,115,75);
    GDSIILine b4(115,75,95,75);
    GDSIILine b5(95,75,95,85);
    GDSIILine b6(95,85,75,85);

    GDSIILine c1(65,10,65,25);
    GDSIILine c2(65,25,85,25);
    GDSIILine c3(85,25,85,35);
    GDSIILine c4(85,35,95,35);
    GDSIILine c5(95,35,95,45);
    GDSIILine c6(95,45,105,45);
    GDSIILine c7(105,45,105,10);
    GDSIILine c8(105,10,65,10);

    GDSIILineContainer cont;
    cont.AddLine(a1);
    cont.AddLine(a2);
    cont.AddLine(a3);
    cont.AddLine(a4);

    cont.AddLine(b1);
    cont.AddLine(b2);
    cont.AddLine(b3);
    cont.AddLine(b4);
    cont.AddLine(b5);
    cont.AddLine(b6);

    cont.AddLine(c1);
    cont.AddLine(c2);
    cont.AddLine(c3);
    cont.AddLine(c4);
    cont.AddLine(c5);
    cont.AddLine(c6);
    cont.AddLine(c7);
    cont.AddLine(c8);

    ContainerPrinter(cont);
    std::cout<<"|-------------------TEST-------------------|"<<std::endl;
    GDSIIDesignEncoder::GetInstance().Encode(cont,10);
    std::cout<<"|-------------------||||-------------------|"<<std::endl;
    return 0;
}
int BoundaryTest()
{
    const int x_min = 20;
    const int y_min = 15;
    const int x_max = 40;
    const int y_max = 35;
    LayerForView l4v;
    std::vector<GDSIIPoint> points = {
        GDSIIPoint(25,40),
        GDSIIPoint(30,40),
        GDSIIPoint(30,30),
        GDSIIPoint(45,30),
        GDSIIPoint(45,20),
        GDSIIPoint(25,20),
        GDSIIPoint(25,40)
    };
    std::vector<GDSIIPoint> points2 = {
        GDSIIPoint(5,18),
        GDSIIPoint(5,30),
        GDSIIPoint(15,30),
        GDSIIPoint(15,45),
        GDSIIPoint(45,45),
        GDSIIPoint(45,18),
        GDSIIPoint(5,18)
    };
    Boundary b,b2;
    b.SetPoints(points,points.size());
    b2.SetPoints(points2,points2.size());
    l4v.AddBoundary(&b);
    l4v.AddBoundary(&b2);
    l4v.GetLineContainerForArea(x_min,y_min,x_max,y_max);
    return 0;
}

int DoublingTest()
{
    GDSIILine a(20,10,20,90);
    GDSIILine b(20,90,80,90);
    GDSIILine c(80,90,80,10);
    GDSIILine d(80,10,20,10);
    GDSIILine m(0,110,110,110);
    GDSIILineContainer C;
    C.AddLine(a);
    C.AddLine(b);
    C.AddLine(c);
    C.AddLine(d);
    C.AddLine(m);
    C.SetAreaHeight(120);
    C.SetAreaWidth(120);
    C.SetBottomX(0);
    C.SetBottomY(0);
    std::cout<<GDSIIDesignEncoder::GetInstance().Encode(C,20);
    return 0;
}

int main(int argc, char *argv[])
{
//    GlobalOptions::SetFileName("D:\\gdsFolder\\Tests\\Bin_AREF_test_with_angle_0");
//    GlobalOptions::SetSourceType(FILE_SOURCE);
//    //GDSIIRecord* rec=RecordSupplier::GetInstance().NextRecord().get();
//    GDSIIDesignReader reader;
//    GDSIIDesign* d=reader.MakeModel().get();
//    delete d;
//GDSIILine l1(GDSIIPoint(5,1),GDSIIPoint(5,3));
//GDSIILine l2(GDSIIPoint(2,3),GDSIIPoint(5,3));
//LineAnalyzer anal;
//GDSIIPoint cross;
//bool areCrossing = anal.GetCrossPoint(l1,l2,cross);
//std::cout<<"Cross["<<(areCrossing? "true":"false")<<"]:["<<cross.GetX()<<","<<cross.GetY()<<"]"<<std::endl;

//----------------------------------------CodePrinter(anal.GetCode(l1,l2));
//GDSIILine ab(2,2,2,8);
//GDSIILine bc(2,8,8,8);
//GDSIILine ad(2,2,11,2);
//GDSIILine ce(8,5,8,8);
//GDSIILine ef(8,5,11,5);
//GDSIILine fd(10,2,11,5);
//GDSIIDesignEncoder &enc = GDSIIDesignEncoder::GetInstance();
//return RunTEST1();
//return RunMAIN(argc,argv);
//return RunDiag2();
//return RunTEST1();
//return largeTest();
//return BoundaryTest();
//    return writerTest();
//return Run3LineTest();
//return DoublingTest();
return RunMAIN(argc,argv);

}
