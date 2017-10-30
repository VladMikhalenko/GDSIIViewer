#include "Boundary.h"

Boundary::Boundary():Element(){
    ID=EL_BOUNDARY;
}
Boundary::~Boundary(){

}

void Boundary::Show()
{
    std::cout<<"---BOUNDARY---"<<std::endl;
    Element::Show();
    std::cout<<"Points:\n";
    //size of dynamic array...???
    for(int i=0;i<amountOfPoints;i++)
    {
        std::cout<<"--["<<points[i].x_coord<<","<<points[i].y_coord<<"]\n";
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

Point* Boundary::GetPoints()
{
    return points.data();
}

void Boundary::SetPoints(Point *points,int amount){
    if(amount>=4 && amount<=200)
    {
        amountOfPoints=amount;
        this->points.clear();
        for(int i=0;i<amount;i++)
            this->points.push_back(points[i]);
        //this->points=new Point[amount];
        //for(int i=0;i<amount;i++)
        //    this->points[i]=points[i];
    }
    else
    {
        //throw AnError();

    }

}
