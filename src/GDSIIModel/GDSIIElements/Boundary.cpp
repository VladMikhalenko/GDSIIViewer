#include "inc/GDSIIModel/GDSIIElements/Boundary.h"

Boundary::Boundary():GDSIIElement()
{
    ID=EL_BOUNDARY;
}
Boundary::~Boundary(){

}

void Boundary::Show()
{
    std::cout<<"---BOUNDARY---"<<std::endl;
    GDSIIElement::Show();
    std::cout<<"Points:\n";
    //size of dynamic array...???
    for(int i=0;i<amountOfPoints;i++)
    {
        std::cout<<"--["<<points[i].GetX()<<","<<points[i].GetY()<<"]\n";
    }
    std::cout<<"\nDATATYPE:"<<DATATYPE<<std::endl;
    std::cout<<"---END BOUNDARY---"<<std::endl;
}

void Boundary::SetDataType(short data_t)
{
    DATATYPE=data_t;
}
short Boundary::GetDataType(){
    return DATATYPE;
}

std::vector<GDSIIPoint> Boundary::GetPoints()
{
    return points;
}

void Boundary::SetPoints(const std::vector<GDSIIPoint> &points,int amount){
    if(amount>=4 && amount<=200)
    {
        amountOfPoints=amount;
        this->points.clear();
        for(int i=0;i<amount;i++)
            this->points.push_back(points[i]);
    }
    else
    {
        //throw AnError();
    }

}
