#include "inc/MathTools/FunctionProvider.h"

FunctionProvider::FunctionProvider()
{

}
int FunctionProvider::GetLineEquationY(int x1,int y1,int x2,int y2, int x_value)
{
    return static_cast<double>((-1)*(((y2-y1)*x_value+x1*(y1-y2)+y1*(x2-x1)))/(double)(x1-x2)+0.5);
}
double FunctionProvider::GetLineEquationY(double x1,double y1,double x2,double y2, double x_value)
{
    return static_cast<double>((-1)*(((y2-y1)*x_value+x1*(y1-y2)+y1*(x2-x1)))/(double)(x1-x2)+0.5);
}

double FunctionProvider::GetLineEquationX(double x1, double y1, double x2, double y2, double y_value)
{
    return ((-1)*((x1-x2)*y_value+x1*(y1-y2)+y1*(x2-x1)))/(y2-y1);
}

int FunctionProvider::GetLineCrossX(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    return -((x1*y2-x2*y1)*(x4-x3)-(x3*y4-x4*y3)*(x2-x1))/((y1-y2)*(x4-x3)-(y3-y4)*(x2-x1));
}

int FunctionProvider::GetLineCrossY(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    return ((y3-y4)*GetLineCrossX(x1,y1,x2,y2,x3,y3,x4,y4)-(x3*y4-x4*y3))/(x4-x3);
}

int FunctionProvider::GetLineCrossY(int x3,int y3, int x4, int y4, int x_value)
{
    return ((y3-y4)*x_value-(x3*y4-x4*y3))/(x4-x3);
}
