#include "Record16_XY.h"


Record16_XY::Record16_XY(int count)
{
    points=new Point[count];
    amountOfPoints=count;
    Point p;
    //printf("Source:%d\n",GlobalOptions::GetSourceType());
    IGDSIISource* source=SourceFactory::GetSource();
    for(int i=0;i<count;i++)
    {
        p.x_coord=BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4);
        p.y_coord=BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4);
        points[i]=p;
    }
    recordID = XY;
}

Record16_XY::Record16_XY(const Record16_XY& orig) {
}

Record16_XY::~Record16_XY() {
}
void Record16_XY::Show()
{
    std::cout<<"<Record16_XY..."<<std::endl;
    for(int i=0;i<GetPointsAmount();i++)
    {
        cout<<"  ["<<points[i].x_coord<<","<<points[i].y_coord<<"]"<<endl;
    }
    std::cout<<"...Record16_XY>"<<std::endl;
}

Point* Record16_XY::GetPoints()
{
    return points;
}

int Record16_XY::GetPointsAmount()
{
    return amountOfPoints;
}
