#ifndef HOTSPOTSCANER_H
#define HOTSPOTSCANER_H
#include "src/GDSIIDesign.h"
#include "QWidget"
#include "QPainter"

class HotSpotScaner
{
    GDSIIDesign* design;
    void CalculateBordersOfMarker(Element* el, Point &leftBottom, Point &leftTop, Point &rightBottom, Point &rightTop);
public:
    HotSpotScaner(GDSIIDesign *gdsii_design);
    LineContainer *ScannLayer(int data_layer, int marker_layer);
};

#endif // HOTSPOTSCANER_H
