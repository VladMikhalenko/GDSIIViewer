#include "mainwindow.h"
#include <QApplication>
#include "inc/LithographyTools/GaussianKernel.h"
#include <memory>
#include <iomanip>
#include "inc/LithographyTools/LineAnalyzer.h"
#include "inc/GUI/GDSIILineContainer.h"
#include "utils/Encoder/GDSIIDesignEncoder.h"
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


int RunViewer(int argc, char *argv[])
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
int RunTest()
{
    GDSIIDesignEncoder &enc = GDSIIDesignEncoder::GetInstance();

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
int main(int argc, char *argv[])
{
//    kernel_type kernel=GaussianKernel::CalculateGaussian2DKernel(100);
//    QImage img("HotSpot_0.jpg");
//    QPainter p(&img);
//    QLine l(50,50,200,200);

//    //std::cout<<FindYCoordT(0.5,0,1.0,255.0,0.75)<<std::endl;
//    //int y=FindYCoord(50,50,10,6,4);
//    ShootBlackRayT(img,QPoint(200,100),kernel);
//    ShootBlackRayT(img,QPoint(200,150),kernel);

//    img.save("Shot_HS_0.jpg","JPG");

//    kernel_type kernel= GaussianKernel::CalculateGaussian2DKernel(2);
//    std::cout << std::setprecision(5) << std::fixed;
//    for (size_t row = 0; row < kernel.size(); row++) {
//        for (size_t col = 0; col < kernel[row].size(); col++)
//          std::cout << kernel[row][col] << ' ';
//        std::cout << '\n';
//    }
//    return 0;
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

//return RunViewer(argc,argv);
return RunTest();
}
