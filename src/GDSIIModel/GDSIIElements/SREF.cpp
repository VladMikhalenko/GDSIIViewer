#include "inc/GDSIIModel/GDSIIElements/SREF.h"

SREF::SREF():
    GDSIIElement()
  , SNAME()
  , MAG(0.0)
  , ANGLE(0.0)
  , magFlag(false)
  , angleFlag(false)
{
    ID=EL_SREF;
}

SREF::~SREF()
{}

std::string SREF::GetSNAME(){
    return SNAME;
}
void SREF::SetSNAME(std::string name){
    SNAME=name;
}

void SREF::SetReference(std::shared_ptr<GDSIIStructure> structure)
{
     _structure=structure;
}
std::shared_ptr<GDSIIStructure> SREF::GetReference()
{
    return _structure;
}

void SREF::Show(){
    std::cout<<"---SREF---:\n";
    GDSIIElement::Show();
    std::cout<<"Point:["<<points[0].GetX()<<","<<points[0].GetY()<<"]\n";
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

void SREF::SetPoints(const std::vector<GDSIIPoint> &source, int amount){
    if(amount>0 && amount<2)
    {
        points.clear();
        points.reserve(1);
        points.push_back(source[0]);;//some kostil
        amountOfPoints=amount;
    }
    else
    {
        //throw AnError
    }
}
