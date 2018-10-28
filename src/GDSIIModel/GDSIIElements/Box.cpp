#include "inc/GDSIIModel/GDSIIElements/Box.h"

Box::Box():GDSIIElement()
{
    ID=EL_BOX;
}

Box::~Box()
{

}

void Box::Show()
{
    std::cout<<"---BOX---"<<std::endl;
    GDSIIElement::Show();
    std::cout<<"Points:\n";
    for(unsigned i=0;i<sizeof(points)/sizeof(points[0]);i++)
    {
        std::cout<<"--["<<points[i].GetX()<<","<<points[i].GetY()<<"]\n";
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

void Box::SetPoints(const std::vector<GDSIIPoint> &source, int amount){
    if(amount==5)//amount>0 && amount<=5)
    {
        points.clear();
        points.reserve(amount);
        amountOfPoints=amount;
        for(int i=0;i<amount;i++)
            points.push_back(source[i]);
    }
    else
    {
        //throw AnError;
    }
}
