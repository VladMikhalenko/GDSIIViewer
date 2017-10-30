#ifndef LAYERFORVIEW_H
#define LAYERFORVIEW_H

#include <vector>
#include "Boundary.h"
#include "Path.h"
#include "SREF.h"
#include "AREF.h"
#include "LineContainer.h"

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

    Boundary* GetBoundaries();
    Path* GetPaths();

    void AddBoundary(Boundary* boundary);
    void AddPath(Path* path);

    LineContainer* GetLineContainerForArea(int x_min,int y_min,int x_max,int y_max);

    template<class T>
    void GatherLinesFromElement(std::vector<T,std::allocator<T>> vect, LineContainer* &container, int area_min_x,int area_min_y, int area_max_x,int area_max_y, int &layer_min_x, int &layer_min_y, int &layer_max_x, int &layer_max_y)
    {
        QPoint cur;
        QPoint next;
        for(int i=0;i<vect.size();i++)
        {
            T el=vect[i];
            Point* el_points=el.GetPoints();

            layer_max_x=el_points[0].x_coord>layer_max_x? el_points[0].x_coord: layer_max_x;
            layer_min_x=el_points[0].x_coord<layer_min_x? el_points[0].x_coord: layer_min_x;
            layer_max_y=el_points[0].y_coord>layer_max_y? el_points[0].y_coord: layer_max_y;
            layer_min_y=el_points[0].y_coord<layer_min_y? el_points[0].y_coord: layer_min_y;

            cur=QPoint(el_points[0].x_coord,el_points[0].y_coord);
            for(int j=1;j<el.GetAmountOfPoints();j++)
            {
                next=QPoint(el_points[j].x_coord,el_points[j].y_coord);
                bool curIsIn=(cur.x()>=area_min_x && cur.y()>=area_min_y && cur.x()<=area_max_x && cur.y()<=area_max_y);
                bool nextIsIn=(next.x()>=area_min_x && next.y()>=area_min_y && next.x()<=area_max_x && next.y()<=area_max_y);
                bool yAreIn=cur.y()>=area_min_y && cur.y()<=area_max_y && next.y()>=area_min_y && next.y()<=area_max_y;
                bool xAreIn=cur.x()>=area_min_x && cur.x()<=area_max_x && next.x()>=area_min_x && next.y()<=area_max_x;
                if(curIsIn || nextIsIn || yAreIn || xAreIn)
                {
                    if(next.x()>layer_max_x)
                        layer_max_x=next.x();
                    else if(next.x()<layer_min_x)
                        layer_min_x=next.x();
                    if(next.y()>layer_max_y)
                        layer_max_y=next.y();
                    else if(next.y()<layer_min_y)
                        layer_min_y=next.y();


                    container->AddLine(QLine(cur,next));
                }
                cur=next;
            }
        }
    }

    void ClearData();

};

#endif // LAYERFORVIEW_H
