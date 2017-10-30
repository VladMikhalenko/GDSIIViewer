#include "LayerForView.h"

LayerForView::LayerForView()
{
    boundCount=0;
    pathCount=0;
}

void LayerForView::AddBoundary(Boundary *boundary){
    boundaries.push_back(*boundary);
    boundCount++;
}
void LayerForView::AddPath(Path *path){
    paths.push_back(*path);
    pathCount++;
}

Boundary* LayerForView::GetBoundaries()
{
    return boundaries.data();
}
Path *LayerForView::GetPaths()
{
    return paths.data();
}

int LayerForView::GetBoundaryAmount()
{
    return boundCount;
}
int LayerForView::GetPathAmount()
{
    return pathCount;
}

LineContainer* LayerForView::GetLineContainerForArea(int x_min, int y_min, int x_max, int y_max){
    LineContainer* container=new LineContainer();
    Boundary* boundArr=GetBoundaries();
    Path* pathArr=GetPaths();

    int layerXMax=INT32_MIN;
    int layerYMax=INT32_MIN;
    int layerXMin=INT32_MAX;
    int layerYMin=INT32_MAX;

/*    QPoint cur;
    QPoint next;
    for(int i=0;i<boundaries.size();i++)
    {
        Boundary* b=&boundArr[i];
        Point* b_points=b->GetPoints();

        layerXMax=b_points[0].x_coord>layerXMax? b_points[0].x_coord: layerXMax;
        layerXMin=b_points[0].x_coord<layerXMin? b_points[0].x_coord: layerXMin;
        layerYMax=b_points[0].y_coord>layerYMax? b_points[0].y_coord: layerYMax;
        layerYMin=b_points[0].y_coord<layerYMin? b_points[0].y_coord: layerYMin;

        cur=QPoint(b_points[0].x_coord,b_points[0].y_coord);
        for(int j=1;j<b->GetAmountOfPoints();j++)
        {
            next=QPoint(b_points[j].x_coord,b_points[j].y_coord);
            if((cur.x()>=x_min && cur.y()>=y_min && cur.x()<=x_max && cur.y()<=y_max) ||
               (next.x()>=x_min && next.y()>=y_min && next.x()<=x_max && next.y()<=y_max)
            )
            {
                if(next.x()>layerXMax)
                    layerXMax=next.x();
                else if(next.x()<layerXMin)
                    layerXMin=next.x();
                if(next.y()>layerYMax)
                    layerYMax=next.y();
                else if(next.y()<layerYMin)
                    layerYMin=next.y();

                container->AddLine(QLine(cur,next));

            }
            cur=next;
        }
    }

    for(int i=0;i<paths.size();i++)
    {
        Path* path=&pathArr[i];
        Point* p_points=path->GetPoints();

        layerXMax=p_points[0].x_coord>layerXMax? p_points[0].x_coord: layerXMax;
        layerXMin=p_points[0].x_coord<layerXMin? p_points[0].x_coord: layerXMin;
        layerYMax=p_points[0].y_coord>layerYMax? p_points[0].y_coord: layerYMax;
        layerYMin=p_points[0].y_coord<layerYMin? p_points[0].y_coord: layerYMin;

        cur=QPoint(p_points[0].x_coord,p_points[0].y_coord);
        for(int j=1;j<path->GetAmountOfPoints();j++)
        {
            next=QPoint(p_points[j].x_coord,p_points[j].y_coord);

            if((cur.x()>=x_min && cur.y()>=y_min && cur.x()<=x_max && cur.y()<=y_max) ||
               (next.x()>=x_min && next.y()>=y_min && next.x()<=x_max && next.y()<=y_max)
            )
            {
                if(next.x()>layerXMax)
                    layerXMax=next.x();
                else if(cur.x()<layerXMin)
                    layerXMin=next.x();
                if(next.y()>layerYMax)
                    layerYMax=next.y();
                else if(next.y()<layerYMin)
                    layerYMin=next.y();
                container->AddLine(QLine(cur,next));
            }


            cur=next;
        }
    }
*/
    GatherLinesFromElement(boundaries,container,x_min,y_min,x_max,y_max,layerXMin,layerYMin,layerXMax,layerYMax);
    GatherLinesFromElement(paths,container,x_min,y_min,x_max,y_max,layerXMin,layerYMin,layerXMax,layerYMax);
    container->SetAreaWidth(layerXMax-layerXMin);//layerXMin<0?layerXMax-layerXMin:layerXMax);
    container->SetAreaHeight(layerYMax-layerYMin);//layerYMin<0?layerYMax-layerYMin:layerYMax);
    container->SetBottomX(layerXMin);
    container->SetBottomY(layerYMin);
    return container;
}
void LayerForView::ClearData()
{
    boundaries.clear();
    paths.clear();
    boundCount=0;
    pathCount=0;
}

int LayerForView::GetLayerHeight()
{
    return layerHeight;
}
int LayerForView::GetLayerWidth()
{
    return layerWidth;
}

