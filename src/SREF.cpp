#include "SREF.h"

SREF::SREF():Element()
{
    angleFlag=false;
    magFlag=false;
    ID=EL_SREF;
}

SREF::~SREF()
{

}

std::string SREF::GetSNAME(){
    return SNAME;
}
void SREF::SetSNAME(std::string name){
    SNAME=name;
}

void SREF::SetReference(Structure *structure)
{
     _structure=structure;
}
Structure* SREF::GetReference()
{
    return _structure;
}

void SREF::Show(){
    std::cout<<"---SREF---:\n";
    Element::Show();
    std::cout<<"Point:["<<point.x_coord<<","<<point.y_coord<<"]\n";
    std::cout<<"\nSNAME:"<<SNAME<<std::endl
             <<"MAG:"<<(HasMAG()? std::to_string(MAG):"not set")<<std::endl
             <<"ANGLE:"<<(HasANGLE()? std::to_string(ANGLE):"not set")<<std::endl;
    //_structure->Show();


    std::cout<<"---END SREF---"<<std::endl;

}

void SREF::SetAngle(double angle)
{
    angleFlag=true;
    ANGLE=angle;
}
double SREF::GetAngle(){
    if(HasANGLE())
        return ANGLE;
    else{return 0;}//временно
        //throw AnError();
}

void SREF::SetMAG(double mag){
    magFlag=true;
    MAG=mag;
}
double SREF::GetMAG()
{
    if(HasMAG())
        return MAG;
    else{ return 1;}//временно
        //throw AnError();
}

bool SREF::HasANGLE()
{
    return angleFlag;
}
bool SREF::HasMAG()
{
    return magFlag;
}

Point* SREF::GetPoints()
{
    return &point;
}
void SREF::SetPoints(Point* p, int amount){
    if(amount>0 && amount<2)
    {
        point=*p;
        amountOfPoints=amount;
        //if(amountOfPoints==1)
        //delete this->point;
        //point=p;
        //amountOfPoints=1;
    }
}
