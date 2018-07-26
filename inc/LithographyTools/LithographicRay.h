#ifndef LITHOGRAPHICRAY_H
#define LITHOGRAPHICRAY_H

#include "QImage"
#include "GaussianKernel.h"
#include "inc/GDSIIGeometry/Primitives/GDSIIPoint.h"
#include "inc/LithographyTools/IntensityField.h"
#include "inc/GDSIIGeometry/Primitives/GDSIILine.h"

class LithographicRay
{
    LithographicRay();
    ~LithographicRay();
public:
    static void ShootColor(QImage *_img,GDSIIPoint point,kernel_type kernel);
    static void ShootBlack(QImage *_img,GDSIIPoint point,kernel_type kernel);
    static void ShootPoint(IntensityField &field, const GDSIIPoint &p, const kernel_type kernel);
    static void ShootLine(IntensityField &field,const GDSIILine &p,const kernel_type kernel,const unsigned step);
    static void ShootField(IntensityField &field, const std::vector<GDSIILine> &lines, const kernel_type &kernel,const unsigned step);

};

#endif // LITHOGRAPHICRAY_H
