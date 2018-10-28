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
int GDSIILineContainer::GetBottomX() const
{
    return bottomX;
}
int GDSIILineContainer::GetBottomY() const
{
    return bottomY;
}

int GDSIILineContainer::GetAreaWidth() const
{
    return areaWidth;
}
int GDSIILineContainer::GetAreaHeight() const
{
    return areaHeight;
}

void GDSIILineContainer::PerformShift()
{
    int x = bottomX < 0 ? -bottomX : 0;
    int y = bottomY < 0 ? -bottomY : 0;
    if(x|y)
    {
        const GDSIIPoint p(x,y);
        for(auto item = lineArray.begin(); item != lineArray.end(); item++)
        {
            item->SetP1(item->GetP1()+p);
            item->SetP2(item->GetP2()+p);
        }
    }
}

constLineContainerIt GDSIILineContainer::Begin() const
{
    return lineArray.begin();
}

constLineContainerIt GDSIILineContainer::End() const
{
    return lineArray.end();
}
