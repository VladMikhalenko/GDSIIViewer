#include "GDSIIConverter.h"
#include "inc/MathTools/FunctionProvider.h"

GDSIIConverter::GDSIIConverter()
{}

QLine GDSIIConverter::Convert(const GDSIILine &line)
{
    return QLine(line.GetP1().GetX(),line.GetP1().GetY(),line.GetP2().GetX(),line.GetP2().GetY());
}

QPoint GDSIIConverter::Convert(const GDSIIPoint &point)
{
    return QPoint(point.GetX(),point.GetY());
}

std::shared_ptr<QImage> GDSIIConverter::Convert(const IntensityField &f)
{
    if(f.GetRows()>0 && f.GetCols()>0)
    {
        std::shared_ptr<QImage> _img=std::shared_ptr<QImage>(new QImage(static_cast<int>(f.GetCols()),static_cast<int>(f.GetRows()),QImage::Format_ARGB32_Premultiplied));
        _img->fill(Qt::white);
        double max=f.GetMax();

        for(int row=0;row<_img->height();row++)
        {
            for(int col=0;col<_img->width();col++)
            {
                double intensity=f[row][col]/max;//normazilation
                int color=static_cast<int>(FunctionProvider::GetLineEquationY(0.0,255.0,1.0,0.0,intensity));
                _img->setPixelColor(row,col,QColor(color,color,color));
                if(color>255 || color<0)
                    printf("strange colo value %d",color);
            }
        }
        return _img;
    }
    else
    {
        return std::shared_ptr<QImage>(nullptr);
    }
}
