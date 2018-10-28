#include "inc/GUI/LayerForView.h"

LayerForView::LayerForView():boundCount(0),pathCount(0)
{}

void LayerForView::AddBoundary(Boundary *boundary){
    boundaries.push_back(*boundary);
    boundCount++;
}
void LayerForView::AddPath(Path *path){
    paths.push_back(*path);
    pathCount++;
}

std::vector<Boundary> LayerForView::GetBoundaries()
{
    return boundaries;
}
std::vector<Path> LayerForView::GetPaths()
{
    return paths;
}

int LayerForView::GetBoundaryAmount()
{
    return boundCount;
}
int LayerForView::GetPathAmount()
{
    return pathCount;
}

std::shared_ptr<GDSIILineContainer> LayerForView::GetLineContainerForArea(int x_min, int y_min, int x_max, int y_max){

    std::shared_ptr<GDSIILineContainer> container=std::make_shared<GDSIILineContainer>(GDSIILineContainer());

    int layerXMax=INT32_MIN;
    int layerYMax=INT32_MIN;
    int layerXMin=INT32_MAX;
    int layerYMin=INT32_MAX;

    GatherLinesFromElementForArea(boundaries,container,x_min,y_min,x_max,y_max,layerXMin,layerYMin,layerXMax,layerYMax);
    GatherLinesFromElementForArea(paths,container,x_min,y_min,x_max,y_max,layerXMin,layerYMin,layerXMax,layerYMax);
    container->SetAreaWidth(x_max-x_min);
    container->SetAreaHeight(y_max-y_min);
    container->SetBottomX(x_min);
    container->SetBottomY(y_min);
    return container;
}
std::shared_ptr<GDSIILineContainer> LayerForView::GetLineContainerToDraw()
{
    std::shared_ptr<GDSIILineContainer> container=std::make_shared<GDSIILineContainer>(GDSIILineContainer());

    const int x_min=INT32_MIN;
    const int y_min=INT32_MIN;
    const int x_max=INT32_MAX;
    const int y_max=INT32_MAX;

    int layerXMax=INT32_MIN;
    int layerYMax=INT32_MIN;
    int layerXMin=INT32_MAX;
    int layerYMin=INT32_MAX;

    GatherLinesFromElementForArea(boundaries,container,x_min,y_min,x_max,y_max,layerXMin,layerYMin,layerXMax,layerYMax);
    GatherLinesFromElementForArea(paths,container,x_min,y_min,x_max,y_max,layerXMin,layerYMin,layerXMax,layerYMax);
    container->SetAreaWidth(layerXMax-layerXMin);
    container->SetAreaHeight(layerYMax-layerYMin);
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

