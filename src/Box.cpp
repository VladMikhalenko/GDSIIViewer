#include "Box.h"

Box::Box():Element()
{
    ID=EL_BOX;
}

Box::~Box()
{

}

void Box::Show()
{
    std::cout<<"---BOX---"<<std::endl;
    Element::Show();
    std::cout<<"Points:\n";
    for(int i=0;i<sizeof(points)/sizeof(points[0]);i++)
    {
        std::cout<<"--["<<points[i].x_coord<<","<<points[i].y_coord<<"]\n";
    }
    std::cout<<"\nBOXTYPE:"<<BOXTYPE<<std::endl;
    std::cout<<"---END BOX---"<<std::endl;
}

void Box::SetBoxType(short b_type){
    BOXTYPE=b_type;
}
short Box::GetBoxType()
{
    return BOXTYPE;
}

Point* Box::GetPoints(){
    return points.data();
}
void Box::SetPoints(Point *points,int amount){
    if(amount==5)//amount>0 && amount<=5)
    {
        this->points.clear();
        amountOfPoints=amount;
        for(int i=0;i<amount;i++)
            this->points.push_back(points[i]);
    }
}
