#ifndef HOTSPOTSCANER_H
#define HOTSPOTSCANER_H
#include "inc/GDSIIModel/GDSIIDesign/GDSIIDesign.h"
#include "QWidget"
#include "QPainter"
#include "inc/LithographyTools/GaussianKernel.h"

class HotSpotScaner
{
    std::shared_ptr<GDSIIDesign> design;
    void CalculateBordersOfMarker(const std::shared_ptr<GDSIIElement> &el, GDSIIPoint &leftBottom, GDSIIPoint &leftTop, GDSIIPoint &rightBottom, GDSIIPoint &rightTop);
public:
    HotSpotScaner(std::shared_ptr<GDSIIDesign> gdsii_design);
    std::shared_ptr<GDSIILineContainer> ScannLayer(int data_layer, int marker_layer);
    //void ShootColorRay(QImage &img,QPoint point, kernel_type kernel);
    //void ShootBlackRay(QImage &img,QPoint point, kernel_type kernel);
};

#endif // HOTSPOTSCANER_H
