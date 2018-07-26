#include "inc/GDSIIModel/GDSIIRecords/Record16_XY.h"


Record16_XY::Record16_XY(int count)
{
    points.resize(count);//=std::vector(count);
    amountOfPoints=count;
    //printf("Source:%d\n",GlobalOptions::GetSourceType());
    IGDSIISource* source=SourceFactory::GetSource();
    for(int i=0;i<count;i++)
    {
        int x=(BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4));
        int y=(BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4));
        points[i]=GDSIIPoint(x,y);
    }
    recordID=XY;
}

Record16_XY::~Record16_XY() {
}
void Record16_XY::Show()
{
    std::cout<<"<Record16_XY..."<<std::endl;
    for(int i=0;i<GetPointsAmount();i++)
    {
        std::cout<<"  ["<<points[i].GetX()<<","<<points[i].GetY()<<"]"<<std::endl;
    }
    std::cout<<"...Record16_XY>"<<std::endl;
}

std::vector<GDSIIPoint> Record16_XY::GetPoints()
{
    return points;
}

int Record16_XY::GetPointsAmount()
{
    return amountOfPoints;
}
