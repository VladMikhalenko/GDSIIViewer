#include "inc/LithographyTools/LithographicRay.h"
#include "inc/MathTools/FunctionProvider.h"

LithographicRay::LithographicRay()
{
}

LithographicRay::~LithographicRay()
{

}
void LithographicRay::ShootColor(QImage *_img, GDSIIPoint point, kernel_type kernel)
{
    if(_img!=nullptr)
    {
        int hSize=kernel.size()/2;
        int initX=point.GetX()-hSize;
        int initY=point.GetY()-hSize;

        for(int x=initX, kx=0;x<point.GetX()+hSize;x++,kx++)
        {
            if(x<0 || x>_img->width()-1) continue;
            for(int y=initY,ky=0;y<point.GetY()+hSize;y++,ky++)
            {
                if(y<0 || y>_img->height()-1) continue;

                int RED=255;
                int GREEN=255,BLUE=0;
                double BOTTOM=0.0,MIDDLE=0.5,MAX=1.0;

                double kIntens=kernel[kx][ky];//kernel weight

                QColor pixCol=_img->pixel(x,y);
                int _pr=pixCol.red();
                int _pg=pixCol.green();
                int _pb=pixCol.blue();
                //вес зеленого текущем пикселе
                double gIntens=FunctionProvider::GetLineEquationX(MIDDLE,BOTTOM,MAX,255.0,pixCol.green());
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
                        GREEN=FunctionProvider::GetLineEquationY(MIDDLE,BOTTOM,MAX,255.0,newIntensityCoef);
                        BLUE=0;
                    }
                    else if(newIntensityCoef>0)
                    {
                        GREEN=BLUE=GREEN-FunctionProvider::GetLineEquationY(BOTTOM,BOTTOM,MIDDLE,255.0,newIntensityCoef);
                    }
                }
                _img->setPixelColor(x,y,QColor(RED,GREEN,BLUE));
            }
        }
    }
    else return;

}

void LithographicRay::ShootBlack(QImage *_img, GDSIIPoint point, kernel_type kernel)
{
    if(_img!=nullptr)
    {
        int hSize=kernel.size()/2;
        int initX=point.GetX()-hSize;
        int initY=point.GetY()-hSize;

        for(int x=initX, kx=0;x<point.GetX()+hSize;x++,kx++)
        {
            if(x<0 || x>_img->width()-1) continue;
            for(int y=initY,ky=0;y<point.GetY()+hSize;y++,ky++)
            {
                if(y<0 || y>_img->height()-1) continue;

                int newColor=255;
                double MIN=0.0,MAX=1.0;

                double kIntens=kernel[kx][ky];//kernel weight

                QColor pixCol=_img->pixel(x,y);
                int _pg=pixCol.green();

                //функция зависимости значения цвета от интенсивности описывается линейной функцией(уравнение прямой):
                //в 0 цвет равен 255, в 1.0 цвет равен 0
                double blackInt=FunctionProvider::GetLineEquationX(MIN,255.0,MAX,0,_pg);

                double newIntensityCoef=blackInt+kIntens<MAX?blackInt+kIntens:MAX-0.01;//blackInt+kIntens<1.0?blackInt+kIntens:0.99;
                newColor=static_cast<int>(FunctionProvider::GetLineEquationY(MIN,255.0,MAX,0.0,newIntensityCoef));
                _img->setPixelColor(x,y,QColor(newColor,newColor,newColor));//r-variable, g,b - constant,

    //            double blackInt=FindXCoord(BOTTOM,MAX*255.0,MAX,0,_pg);

    //            double newIntensityCoef=blackInt+kIntens<MAX?blackInt+kIntens:MAX-0.01;//blackInt+kIntens<1.0?blackInt+kIntens:0.99;
    //            newColor=static_cast<int>(FindYCoord(BOTTOM,MAX*255.0,MAX,0.0,newIntensityCoef));
    //            img.setPixelColor(x,y,QColor(newColor,newColor,newColor));//r-variable, g,b - constant,
            }
        }
    }

}

void LithographicRay::ShootPoint(IntensityField &field, const GDSIIPoint &p, const kernel_type kernel)
{
    if(field.GetRows()>0 && field.GetCols()>0 && kernel.size()>0)
    {
        int hSize=kernel.size()/2;
        int initX=p.GetX()-hSize;
        int initY=p.GetY()-hSize;

        for(int x=initX, kx=0;x<p.GetX()+hSize;x++,kx++)
        {
            if(x<0 || x>field.GetRows()-1) continue;
            for(int y=initY,ky=0;y<p.GetY()+hSize;y++,ky++)
            {
                if(y<0 || y>field.GetCols()-1) continue;

                double kIntens=kernel[kx][ky];//kernel weight
                double fIntens=field[x][y];
                field[x][y]+=kIntens;
                double ixy=field[x][y];
                if(ixy>field.GetMax())
                    field.SetMax(ixy);
                else if(ixy<field.GetMin())
                    field.SetMin(ixy);
            }
        }
    }

}
void LithographicRay::ShootLine(IntensityField &field, const GDSIILine &p, const kernel_type kernel, const unsigned step)
{
    if(field.GetCols()>0 && field.GetRows()>0 && kernel.size()>0 && step>0)
    {
        int x1=p.GetP1().GetX();
        int y1=p.GetP1().GetY();

        int x2=p.GetP2().GetX();
        int y2=p.GetP2().GetY();

        if(x1!=x2)
        {
            int x=x1;
            int move=x1<x2?step:-step;
            for(;x1<x2?x<x2:x>x2;x+=move)
            {
                int y=FunctionProvider::GetLineEquationY(x1,y1,x2,y2,x);
                if(x<0 || y<0|| x>static_cast<int>(field.GetRows())|| y>static_cast<int>(field.GetCols()))
                    continue;
                LithographicRay::ShootPoint(field,GDSIIPoint(x,y),kernel);
            }
        }
        else
        {
            int y=y1;
            int move=y1<y2?step:-step;
            for(;y1<y2?y<y2:y>y2;y+=move)
            {
                if(x1<0 || x2<0 || x1>static_cast<int>(field.GetRows()) ||
                        x2>static_cast<int>(field.GetRows()) || y<0||
                        y>static_cast<int>(field.GetCols()))
                    continue;
                LithographicRay::ShootPoint(field,GDSIIPoint(x1,y),kernel);
            }
        }
    }
}

void LithographicRay::ShootField(IntensityField &field, const std::vector<GDSIILine> &lines, const kernel_type &kernel,const unsigned step)
{
    if(field.GetCols()>0 && field.GetRows()>0 && lines.size()>0 && kernel.size()>0)
    {
        for(auto it=lines.begin();it!=lines.end();it++)
        {
            ShootLine(field,*it,kernel,step);
        }
    }
}
