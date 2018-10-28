#include "HotSpotScaner.h"
#include "inc/LithographyTools/LithographicRay.h"
#include "inc/MathTools/FunctionProvider.h"
#include "inc/LithographyTools/GaussianProcessor.h"

#include "utils/GDSIIPainter/GDSIIImageBuilder.h"
#include "utils/Convert/GDSIIConverter.h"
#include <iostream>

HotSpotScaner::HotSpotScaner(std::shared_ptr<GDSIIDesign> gdsii_design)
{
    design=gdsii_design;
}
void HotSpotScaner::ExtractAllMarkedAreasAsJPG(int data_layer, int marker_layer)
{
    LayerForView data   = *design->GetLayerForView(data_layer);
    LayerForView marker = *design->GetLayerForView(marker_layer);
    GDSIIPoint leftBot(INT32_MAX,INT32_MAX);
    GDSIIPoint rightTop(INT32_MIN,INT32_MIN);
    GDSIIPoint leftTop, rightBot;
    QImage image;
    for(int b_index = 0; b_index <marker.GetBoundaryAmount();b_index++)
    {
        image.fill(Qt::white);
        leftBot.SetX(INT32_MAX);
        leftBot.SetY(INT32_MAX);
        rightTop.SetX(INT32_MIN);
        rightTop.SetY(INT32_MIN);

        Boundary b_i=marker.GetBoundaries()[b_index];
        CalculateBordersOfMarker(std::dynamic_pointer_cast<GDSIIElement,Boundary>(std::make_shared<Boundary>(b_i)),leftBot,leftTop,rightBot,rightTop);
        GDSIILineContainer extracted = *data.GetLineContainerForArea(leftBot.GetX(),leftBot.GetY(),rightTop.GetX(),rightTop.GetY());
        GDSIIImageBuilder::DrawLineContainerOnImage(image, extracted);
        image.save(QString::fromStdString(std::string("[HotSpot_"+std::to_string(static_cast<long long>(b_index))+"].jpg")),"JPG");
    }
}
void HotSpotScaner::ExtractMarkedAreasWithGaussAsJPG(int data_layer, int marker_layer)
{
    GaussianProcessor gProc(1199,1.0,60,20);
    LayerForView data   =*design->GetLayerForView(data_layer);
    LayerForView marker =*design->GetLayerForView(marker_layer);
    QImage image;
    GDSIIPoint leftBot(INT32_MAX,INT32_MAX);
    GDSIIPoint rightTop(INT32_MIN,INT32_MIN);
    GDSIIPoint leftTop, rightBot;
    int boundsNum = marker.GetBoundaryAmount();
    for(int b_index = 0; b_index < boundsNum;b_index++)
    {
        leftBot.SetX(INT32_MAX);
        leftBot.SetY(INT32_MAX);
        rightTop.SetX(INT32_MIN);
        rightTop.SetY(INT32_MIN);

        Boundary b_i=marker.GetBoundaries()[b_index];
        CalculateBordersOfMarker(std::dynamic_pointer_cast<GDSIIElement,Boundary>(std::make_shared<Boundary>(b_i)),leftBot,leftTop,rightBot,rightTop);
        GDSIILineContainer extracted = *data.GetLineContainerForArea(leftBot.GetX(),leftBot.GetY(),rightTop.GetX(),rightTop.GetY());
        IntensityField field(1,1);
        gProc.ProcessLineContainer(field, extracted);
        image = GDSIIConverter::GetInstance().Convert(field);
        GDSIIImageBuilder::DrawLineContainerOnImage(image,extracted);
        image.save(QString::fromStdString(std::string("[Field]"+std::to_string(static_cast<long long>(b_index))+".jpg")),"JPG");
    }
}
std::vector<GDSIILineContainer> HotSpotScaner::ExtractAllMarkedAreas(int data_layer, int marker_layer)
{
    std::vector<GDSIILineContainer> areas;
    LayerForView data   = *design->GetLayerForView(data_layer);
    LayerForView marker = *design->GetLayerForView(marker_layer);
    GDSIIPoint leftBot(INT32_MAX,INT32_MAX);
    GDSIIPoint rightTop(INT32_MIN,INT32_MIN);
    GDSIIPoint leftTop, rightBot;
    areas.reserve(static_cast<size_t>(marker.GetBoundaryAmount()));
    for(int b_index = 0; b_index <marker.GetBoundaryAmount();b_index++)
    {
        leftBot.SetX(INT32_MAX);
        leftBot.SetY(INT32_MAX);
        rightTop.SetX(INT32_MIN);
        rightTop.SetY(INT32_MIN);

        Boundary b_i=marker.GetBoundaries()[b_index];
        CalculateBordersOfMarker(std::dynamic_pointer_cast<GDSIIElement,Boundary>(std::make_shared<Boundary>(b_i)),leftBot,leftTop,rightBot,rightTop);
        GDSIILineContainer extracted = *data.GetLineContainerForArea(leftBot.GetX(),leftBot.GetY(),rightTop.GetX(),rightTop.GetY());
        areas.push_back(extracted);
    }
    return areas;
}
std::shared_ptr<GDSIILineContainer> HotSpotScaner::ScannLayer(int data_layer, int marker_layer)
{
    LayerForView data=*design->GetLayerForView(data_layer);
    LayerForView marker=*design->GetLayerForView(marker_layer);
    GDSIIPoint leftBot(INT32_MAX,INT32_MAX);

    GDSIIPoint rightTop(INT32_MIN,INT32_MIN);

    GDSIIPoint leftTop;
    GDSIIPoint rightBot;

    QPainter* paint=new QPainter();
    paint->setPen(QPen(Qt::white,10.0));
    paint->setBrush(QBrush(Qt::white));
    paint->setRenderHint(QPainter::Antialiasing,true);

    int radius=100;
    unsigned step=20;//radius/3;//20;
    int kernel_size=1199;
    double sigma=60;
    double alpha=1.0;
    kernel_type kernel=GaussianKernel::CalculateGaussian2DKernel(kernel_size,sigma,alpha);

    for(int i=0;i<marker.GetBoundaryAmount();i++)
    {
        leftBot.SetX(INT32_MAX);
        leftBot.SetY(INT32_MAX);
        rightTop.SetX(INT32_MIN);
        rightTop.SetY(INT32_MIN);

        Boundary b_i=marker.GetBoundaries()[i];
        CalculateBordersOfMarker(std::dynamic_pointer_cast<GDSIIElement,Boundary>(std::make_shared<Boundary>(b_i)),leftBot,leftTop,rightBot,rightTop);
        std::shared_ptr<GDSIILineContainer> result= data.GetLineContainerForArea(leftBot.GetX(),leftBot.GetY(),rightTop.GetX(),rightTop.GetY());
        int area_width=rightTop.GetX()-leftBot.GetX();
        int area_height=rightTop.GetY()-rightBot.GetY();

        std::shared_ptr<QImage> image=std::shared_ptr<QImage>(new QImage(area_width,area_height,QImage::Format_ARGB32_Premultiplied));
        image->fill(Qt::white);

        IntensityField field(area_width,area_height);

        for(int j=0;j<result->GetAmount();j++)
        {
            GDSIILine l_j=result->GetArray()[j];

            int bottomX=leftBot.GetX();//result->GetBottomX();
            int bottomY=leftBot.GetY();//result->GetBottomY();

            int new_x1=l_j.GetP1().GetX()-bottomX;
            int new_y1=area_height-(l_j.GetP1().GetY()-bottomY);
            int new_x2=l_j.GetP2().GetX()-bottomX;
            int new_y2=area_height-(l_j.GetP2().GetY()-bottomY);

            LithographicRay::ShootLine(field,GDSIILine(new_x1,new_y1,new_x2,new_y2),kernel,step);

//            QLine new_l_j(new_x1,new_y1,new_x2,new_y2);
//            paint->begin(image);
//            paint->drawLine(new_l_j);
//            paint->end();
        }
            //made dark colors and now it's the same situation, nothing is visible
//            if(new_x1!=new_x2)
//            {
//                int x=new_x1;
//                int move=new_x1<new_x2?step:-step;
//                for(;new_x1<new_x2?x<new_x2:x>new_x2;x+=move)
//                {
//                    int y=FunctionProvider::GetLineEquationY(new_x1,new_y1,new_x2,new_y2,x);
//                    if(x<0 || y<0|| x>area_width|| y>area_height)
//                        continue;
//                    LithographicRay::ShootBlack(image,GDSIIPoint(x,y),kernel);
//                }
//            }
//            else
//            {
//                int y=new_y1;
//                int move=new_y1<new_y2?step:-step;
//                for(;new_y1<new_y2?y<new_y2:y>new_y2;y+=move)
//                {
//                    if(new_x1<0 || new_x2<0 ||
//                       new_x1>area_width || new_x2>area_width||
//                       y<0|| y>area_height)
//                        continue;
//                    LithographicRay::ShootBlack(image,GDSIIPoint(new_x1,y),kernel);
//                }
//            }
        //}
        //image->save("HotSpot_"+QString::number(i)+".jpg","JPG");        
        //ShootBlackRay(*image,QPoint(radius,radius),kernel);
//ZAKOMENCHENO------------------------------------------------------------------------------------------V
//        image=GDSIIConverter::GetInstance().Convert(field);
//        for(int j=0;j<result->GetAmount();j++)
//        {
//            GDSIILine l_j=result->GetArray()[j];

//            int bottomX=leftBot.GetX();//result->GetBottomX();
//            int bottomY=leftBot.GetY();//result->GetBottomY();

//            int new_x1=l_j.GetP1().GetX()-bottomX;
//            int new_y1=area_height-(l_j.GetP1().GetY()-bottomY);
//            int new_x2=l_j.GetP2().GetX()-bottomX;
//            int new_y2=area_height-(l_j.GetP2().GetY()-bottomY);


//            QLine new_l_j(new_x1,new_y1,new_x2,new_y2);
//            paint->begin(image.get());
//            paint->drawLine(new_l_j);
//            paint->end();
//        }
//        image->save("SH_HS_"+QString::number(i)+".jpg","JPG");
//        image.reset();
    }
    return nullptr;//костыль!!!!!!!
}
void HotSpotScaner::PerformScanning(int data_layer, int marker_layer)
{
    //UNNECCESSARY
    auto markedAreas = ExtractAllMarkedAreas(data_layer,marker_layer);
    GaussianProcessor gProc(1199,1.0,60,20);
    static size_t count = markedAreas.size();
    for(auto it = markedAreas.begin(); it!=markedAreas.end();it++)
    {
        IntensityField field(1,1);
        gProc.ProcessLineContainer(field, *it);
        QImage img = GDSIIConverter::GetInstance().Convert(field);
        //QImage(*.get()).save("TestImg_"+QString::number(it-markedAreas.begin())+".jpg","JPG");
        GDSIIImageBuilder imb;
        //QImage img;
        //imb.DrawLineContainerOnImage(img,QString("DrawTestImg").toStdString()+QString::number(it-markedAreas.begin()).toStdString(),*it);
        printf("Scanned areas: %d",count--);
    }

}
void HotSpotScaner::CalculateBordersOfMarker(const std::shared_ptr<GDSIIElement> &el, GDSIIPoint &leftBottom, GDSIIPoint &leftTop, GDSIIPoint &rightBottom, GDSIIPoint &rightTop)
{
    for(size_t i=0;i<static_cast<size_t>(el->GetAmountOfPoints());i++)
    {
        GDSIIPoint p_i=el->GetPointAt(i);
        leftBottom=(p_i.GetX()<leftBottom.GetX() && p_i.GetY()<leftBottom.GetY())?p_i:leftBottom;
        rightTop  =(p_i.GetX()>rightTop.GetX()   && p_i.GetY()>rightTop.GetY())  ?p_i:rightTop;
    }
    rightBottom.SetX(rightTop.GetX());
    rightBottom.SetY(leftBottom.GetY());

    leftTop.SetX(leftBottom.GetX());
    leftTop.SetY(rightTop.GetY());

}

//void HotSpotScaner::ShootColorRay(QImage &img,QPoint point,kernel_type kernel)
//{
//    int hSize=kernel.size()/2;
//    int initX=point.GetX()-hSize;
//    int initY=point.GetY()-hSize;

//    for(int x=initX, kx=0;x<point.GetX()+hSize;x++,kx++)
//    {
//        if(x<0 || x>img.width()-1) continue;
//        for(int y=initY,ky=0;y<point.GetY()+hSize;y++,ky++)
//        {
//            if(y<0 || y>img.height()-1) continue;

//            int RED=255;
//            int GREEN=255,BLUE=0;
//            double BOTTOM=0.0,MIDDLE=0.5,MAX=1.0;

//            double kIntens=kernel[kx][ky];//kernel weight

//            QColor pixCol=img.pixel(x,y);
//            int _pr=pixCol.red();
//            int _pg=pixCol.green();
//            int _pb=pixCol.blue();
//            //вес зеленого текущем пикселе
//            double gIntens=FindXCoord(MIDDLE,BOTTOM,MAX,255.0,pixCol.green());
//            //интерпретация веса зеленого: если пискель имеет красно-зеленый оттенок,
//            //то коэфициент рассматривается без изменений, иначе находим значение равное разнице 1 и веса
//            double greenInterpret=(_pr==255 && _pg>0 && _pb==0)?gIntens:1.0-gIntens;

//            double newIntensityCoef=greenInterpret+kIntens<1.0?greenInterpret+kIntens:0.99;
//            if(pixCol.green()<20 && pixCol.red()<20 && pixCol.blue()<20)
//            {
//                //if selected pixel color is close to black, then we don't change it's color
//                RED=pixCol.red();
//                GREEN=pixCol.green();
//                BLUE=pixCol.blue();
//            }
//            else
//            {
//                if(newIntensityCoef>=0.5)
//                {
//                    GREEN=FindYCoord(MIDDLE,BOTTOM,MAX,255.0,newIntensityCoef);
//                    BLUE=0;
//                }
//                else if(newIntensityCoef>0)
//                {
//                    GREEN=BLUE=GREEN-FindYCoord(BOTTOM,BOTTOM,MIDDLE,255.0,newIntensityCoef);
//                }
//            }
//            img.setPixelColor(x,y,QColor(RED,GREEN,BLUE));
//        }
//    }
//}

//void HotSpotScaner::ShootBlackRay(QImage &img,QPoint point,kernel_type kernel)
//{
//    int hSize=kernel.size()/2;
//    int initX=point.GetX()-hSize;
//    int initY=point.GetY()-hSize;

//    for(int x=initX, kx=0;x<point.GetX()+hSize;x++,kx++)
//    {
//        if(x<0 || x>img.width()-1) continue;
//        for(int y=initY,ky=0;y<point.GetY()+hSize;y++,ky++)
//        {
//            if(y<0 || y>img.height()-1) continue;

//            int newColor=255;
//            double MIN=0.0,MAX=1.0;

//            double kIntens=kernel[kx][ky];//kernel weight

//            QColor pixCol=img.pixel(x,y);
//            int _pg=pixCol.green();

//            //функция зависимости значения цвета от интенсивности описывается линейной функцией(уравнение прямой):
//            //в 0 цвет равен 255, в 1.0 цвет равен 0
//            double blackInt=FindXCoord(MIN,255.0,MAX,0,_pg);

//            double newIntensityCoef=blackInt+kIntens<MAX?blackInt+kIntens:MAX-0.01;//blackInt+kIntens<1.0?blackInt+kIntens:0.99;
//            newColor=static_cast<int>(FindYCoord(MIN,255.0,MAX,0.0,newIntensityCoef));
//            img.setPixelColor(x,y,QColor(newColor,newColor,newColor));//r-variable, g,b - constant,

////            double blackInt=FindXCoord(BOTTOM,MAX*255.0,MAX,0,_pg);

////            double newIntensityCoef=blackInt+kIntens<MAX?blackInt+kIntens:MAX-0.01;//blackInt+kIntens<1.0?blackInt+kIntens:0.99;
////            newColor=static_cast<int>(FindYCoord(BOTTOM,MAX*255.0,MAX,0.0,newIntensityCoef));
////            img.setPixelColor(x,y,QColor(newColor,newColor,newColor));//r-variable, g,b - constant,
//        }
//    }
//}
