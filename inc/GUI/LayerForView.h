#ifndef LAYERFORVIEW_H
#define LAYERFORVIEW_H

#include <vector>
#include "inc/GDSIIModel/GDSIIElements/Boundary.h"
#include "inc/GDSIIModel/GDSIIElements/Path.h"
#include "inc/GDSIIModel/GDSIIElements/SREF.h"
#include "inc/GDSIIModel/GDSIIElements/AREF.h"
#include "GDSIILineContainer.h"

class LayerForView
{
    std::vector<Boundary> boundaries;
    std::vector<Path> paths;

    int layerWidth;
    int layerHeight;

    int boundCount;
    int pathCount;

public:
    LayerForView();

    int GetLayerWidth();
    int GetLayerHeight();

    int GetBoundaryAmount();
    int GetPathAmount();

    std::vector<Boundary> GetBoundaries();
    std::vector<Path> GetPaths();

    void AddBoundary(Boundary* boundary);
    void AddPath(Path* path);

    std::shared_ptr<GDSIILineContainer> GetLineContainerForArea(int x_min,int y_min,int x_max,int y_max);

    template<class T>
    void GatherLinesFromElement(std::vector<T,std::allocator<T>> vect, std::shared_ptr<GDSIILineContainer> &container, int area_min_x,int area_min_y, int area_max_x,int area_max_y, int &layer_min_x, int &layer_min_y, int &layer_max_x, int &layer_max_y)
    {
        GDSIIPoint cur;
        GDSIIPoint next;
        for(int i=0;i<vect.size();i++)
        {
            T el=vect[i];
            //std::vector<GDSIIPoint> el_points=it.GetPoints();//el.GetPoints();
            //std::vector<GDSIIPoint>::iterator el_it=el.GetPoints().begin();
//            layer_max_x=el_points[0].GetX()>layer_max_x? el_points[0].GetX(): layer_max_x;
//            layer_min_x=el_points[0].GetX()<layer_min_x? el_points[0].GetX(): layer_min_x;
//            layer_max_y=el_points[0].GetY()>layer_max_y? el_points[0].GetY(): layer_max_y;
//            layer_min_y=el_points[0].GetY()<layer_min_y? el_points[0].GetY(): layer_min_y;
            layer_max_x=el.GetPoints()[0].GetX()>layer_max_x? el.GetPoints()[0].GetX(): layer_max_x;
            layer_min_x=el.GetPoints()[0].GetX()<layer_min_x? el.GetPoints()[0].GetX(): layer_min_x;
            layer_max_y=el.GetPoints()[0].GetY()>layer_max_y? el.GetPoints()[0].GetY(): layer_max_y;
            layer_min_y=el.GetPoints()[0].GetY()<layer_min_y? el.GetPoints()[0].GetY(): layer_min_y;


            cur=GDSIIPoint(el.GetPoints()[0].GetX(),el.GetPoints()[0].GetY());
            for(int j=1;j<el.GetAmountOfPoints();j++)
            {
                next=GDSIIPoint(el.GetPoints()[j].GetX(),el.GetPoints()[j].GetY());//el_points[j].GetX(),el_points[j].GetY());
                bool curIsIn=(cur.GetX()>=area_min_x && cur.GetY()>=area_min_y && cur.GetX()<=area_max_x && cur.GetY()<=area_max_y);
                bool nextIsIn=(next.GetX()>=area_min_x && next.GetY()>=area_min_y && next.GetX()<=area_max_x && next.GetY()<=area_max_y);
                bool yAreIn=cur.GetY()>=area_min_y && cur.GetY()<=area_max_y && next.GetY()>=area_min_y && next.GetY()<=area_max_y;
                bool xAreIn=cur.GetX()>=area_min_x && cur.GetX()<=area_max_x && next.GetX()>=area_min_x && next.GetY()<=area_max_x;
                if(curIsIn || nextIsIn || yAreIn || xAreIn)
                {
                    if(next.GetX()>layer_max_x)
                        layer_max_x=next.GetX();
                    else if(next.GetX()<layer_min_x)
                        layer_min_x=next.GetX();
                    if(next.GetY()>layer_max_y)
                        layer_max_y=next.GetY();
                    else if(next.GetY()<layer_min_y)
                        layer_min_y=next.GetY();


                    container->AddLine(GDSIILine(cur,next));
                }
                cur=next;
            }
        }
    }

    void ClearData();

};

#endif // LAYERFORVIEW_H
