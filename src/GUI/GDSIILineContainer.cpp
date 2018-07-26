#include "inc/GUI/GDSIILineContainer.h"

GDSIILineContainer::GDSIILineContainer():
    areaHeight(0),
    areaWidth(0),
    bottomX(INT32_MAX),
    bottomY(INT32_MAX)
{}

std::vector<GDSIILine>& GDSIILineContainer::GetArray()
{
    return lineArray;
}

int GDSIILineContainer::GetAmount()
{
    return lineArray.size();
}

void GDSIILineContainer::AddLine(GDSIILine line)
{
    lineArray.push_back(line);
//    SetBottomX(line.GetP1().GetX()<bottomX?line.GetP1().GetX():bottomX);
//    SetBottomY(line.GetP1().GetY()<bottomY?line.GetP1().GetY():bottomY);
//    SetBottomX(line.GetP2().GetX()<bottomX?line.GetP2().GetX():bottomX);
//    SetBottomY(line.GetP2().GetY()<bottomY?line.GetP2().GetY():bottomY);
}

void GDSIILineContainer::SetAreaWidth(int width)
{
    areaWidth=width;
}
void GDSIILineContainer::SetAreaHeight(int height)
{
    areaHeight=height;
}
void GDSIILineContainer::SetBottomX(int x_value)
{
    bottomX=x_value;
}
void GDSIILineContainer::SetBottomY(int y_value){
    bottomY=y_value;
}
int GDSIILineContainer::GetBottomX()
{
    return bottomX;
}
int GDSIILineContainer::GetBottomY()
{
    return bottomY;
}

int GDSIILineContainer::GetAreaWidth()
{
    return areaWidth;
}
int GDSIILineContainer::GetAreaHeight()
{
    return areaHeight;
}
