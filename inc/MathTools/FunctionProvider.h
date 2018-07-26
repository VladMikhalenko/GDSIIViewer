#ifndef FUNCTIONPROVIDER_H
#define FUNCTIONPROVIDER_H


class FunctionProvider
{
    FunctionProvider();
public:
    static int GetLineEquationY(int x1,int y1,int x2,int y2, int x_value);
    static double GetLineEquationY(double x1,double y1,double x2,double y2, double x_value);
    //static int GetLineEquationX(int x1, int y1, int x2, int y2, int y_value);
    static double GetLineEquationX(double x1, double y1, double x2, double y2, double y_value);

    static int GetLineCrossX(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
    static int GetLineCrossY(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
    static int GetLineCrossY(int x3, int y3, int x4, int y4, int x_value);
};

#endif // FUNCTIONPROVIDER_H
