#include "HotSpotScaner.h"

HotSpotScaner::HotSpotScaner(GDSIIDesign* gdsii_design)
{
    design=gdsii_design;
}

LineContainer* HotSpotScaner::ScannLayer(int data_layer, int marker_layer)
{
    LayerForView data=*design->GetLayerForView(data_layer);
    LayerForView marker=*design->GetLayerForView(marker_layer);
    Point leftBot;

    Point rightTop;

    Point leftTop;
    Point rightBot;

    QPainter* paint=new QPainter();
    paint->setPen(QPen(Qt::black,10.0));
    paint->setBrush(QBrush(Qt::black));
    paint->setRenderHint(QPainter::Antialiasing,true);

    for(int i=0;i<marker.GetBoundaryAmount();i++)
    {
        leftBot.x_coord=INT32_MAX;
        leftBot.y_coord=INT32_MAX;
        rightTop.x_coord=INT32_MIN;
        rightTop.y_coord=INT32_MIN;

        Boundary b_i=marker.GetBoundaries()[i];
        CalculateBordersOfMarker(dynamic_cast<Element*>(&b_i),leftBot,leftTop,rightBot,rightTop);
        LineContainer* result= data.GetLineContainerForArea(leftBot.x_coord,leftBot.y_coord,rightTop.x_coord,rightTop.y_coord);
        int area_width=rightTop.x_coord-leftBot.x_coord;
        int area_height=rightTop.y_coord-rightBot.y_coord;

        QImage* image=new QImage(area_width,area_height,QImage::Format_ARGB32_Premultiplied);
        image->fill(Qt::white);
        for(int j=0;j<result->GetAmount();j++)
        {

            QLine l_j=result->GetArray()[j];

            int bottomX=leftBot.x_coord;//result->GetBottomX();
            int bottomY=leftBot.y_coord;//result->GetBottomY();

            int new_x1=l_j.p1().x()-bottomX;
            int new_y1=area_height-(l_j.p1().y()-bottomY);
            int new_x2=l_j.p2().x()-bottomX;
            int new_y2=area_height-(l_j.p2().y()-bottomY);

            QLine new_l_j(new_x1,new_y1,new_x2,new_y2);
            paint->begin(image);
            paint->drawLine(new_l_j);
            paint->end();
        }
        image->save("HotSpot_"+QString::number(i)+".jpg","JPG");
        delete image;
    }
}

void HotSpotScaner::CalculateBordersOfMarker(Element *el, Point &leftBottom, Point &leftTop, Point &rightBottom, Point &rightTop)
{
    for(int i=0;i<el->GetAmountOfPoints();i++)
    {
        Point p_i=el->GetPoints()[i];
        leftBottom=(p_i.x_coord<leftBottom.x_coord && p_i.y_coord<leftBottom.y_coord)?p_i:leftBottom;
        rightTop=(p_i.x_coord>rightTop.x_coord && p_i.y_coord>rightTop.y_coord)?p_i:rightTop;
    }
    rightBottom.x_coord=rightTop.x_coord;
    rightBottom.y_coord=leftBottom.y_coord;

    leftTop.x_coord=leftBottom.x_coord;
    leftTop.y_coord=rightTop.y_coord;
}
