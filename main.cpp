#include "mainwindow.h"
#include <QApplication>
#include "inc/LithographyTools/GaussianKernel.h"
#include <memory>
#include <iomanip>
#include "inc/LithographyTools/LineAnalyzer.h"
#include "inc/GUI/GDSIILineContainer.h"
#include "utils/Encoder/GDSIIDesignEncoder.h"
#include <fstream>

#include <Python.h>
#include "utils/Python/PythonHelper/PythonHelper.h"
#include "utils/Python/PythonHelper/PythonModule.h"
#include "utils/Python/PythonHelper/PythonMethod.h"
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
    GDSIILine a(20,20,20,90);
    GDSIILine b(20,90,80,90);
    GDSIILine c(80,90,80,20);
    GDSIILine d(80,20,20,20);
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
    std::cout<<GDSIIDesignEncoder::GetInstance().EncodeSPApproach(C,20);
    return 0;
}
int ValidationTest()
{
    GDSIILine a(0,20,40,20);
    GDSIILine b(40,20,40,100);
    GDSIILine c(40,100,80,100);
    GDSIILine d(80,100,80,20);
    GDSIILine e(80,20,100,20);

    GDSIILineContainer C;
    C.AddLine(a);
    C.AddLine(b);
    C.AddLine(c);
    C.AddLine(d);
    C.AddLine(e);
    C.SetAreaHeight(120);
    C.SetAreaWidth(120);
    C.SetBottomX(0);
    C.SetBottomY(0);
    std::cout<<GDSIIDesignEncoder::GetInstance().EncodeSPApproach(C,20);
    return 0;
}
int PyTest()
{
//    PythonHelper::GetInstance();
//    PythonModule numpy("numpy");
//    PythonMethod add(numpy,"add");
//    PyObject* p5 = PyLong_FromLong(5);
//    PyObject* p4 = PyLong_FromLong(4);
//    PyObject* tpl = PyTuple_New(2);
//    PyTuple_SetItem(tpl,0,p5);
//    PyTuple_SetItem(tpl,1,p4);
//    std::cout<<PyLong_AsLong(add.Execute(tpl));
//    Py_DECREF(p5);
//    Py_DECREF(p4);
//    Py_DECREF(tpl);
    Py_Initialize();
    PyRun_SimpleString("import numpy as np\nprint(np.add(5,3))");
    Py_Finalize();
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
//Py_Initialize();
//PyRun_SimpleString("print('Hello world')");
//Py_Finalize();

    // Initialize the Python interpreter.

//    Py_Initialize();
//    PyObject* pName, *pModule, *pFunc;
//    pName = PyUnicode_FromString("numpy");
//    pModule = PyImport_Import(pName);
//    Py_DECREF(pName);
//    if(pModule != NULL)
//    {
//        pFunc = PyObject_GetAttrString(oModule,"array");
//    }
//    Py_DECREF(pModule);

    //PyRun_SimpleString("print('Hello world')");
    // Create some Python objects that will later be assigned values.

//    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;

//    // Convert the file name to a Python string.

//    pName = PyUnicode_FromString("Simple");//PyString_FromString("Sample");
//    // Import the file as a Python module.

//    pModule = PyImport_Import(pName);

//    // Create a dictionary for the contents of the module.

//    pDict = PyModule_GetDict(pModule);

//    // Get the add method from the dictionary.

//    pFunc = PyDict_GetItemString(pDict, "add");

//    // Create a Python tuple to hold the arguments to the method.

//    pArgs = PyTuple_New(2);

//    // Convert 2 to a Python integer.

//    pValue = PyLong_FromLong(2);

//    // Set the Python int as the first and second arguments to the method.

//    PyTuple_SetItem(pArgs, 0, pValue);

//    PyTuple_SetItem(pArgs, 1, pValue);

//    // Call the function with the arguments.

//    PyObject* pResult = PyObject_CallObject(pFunc, pArgs);

//    // Print a message if calling the method failed.

//    if(pResult == NULL)

//    printf("Calling the add method failed.\n");

//    // Convert the result to a long from a Python object.

//    long result = PyLong_AsLong(pResult);

    // Destroy the Python interpreter.

    //Py_Finalize();

    // Print the result.

    //printf("The result is %d.\n", result); std::cin.ignore();
    //return 0;
    return PyTest();
//return RunMAIN(argc,argv);
}
