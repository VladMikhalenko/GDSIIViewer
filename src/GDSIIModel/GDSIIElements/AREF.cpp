#include "inc/GDSIIModel/GDSIIElements/AREF.h"

AREF::AREF():
    GDSIIElement(),
    angleFlag(false),
    magFlag(false)
{
    ID=EL_AREF;
}

AREF::~AREF()
{}

short AREF::GetCOL(){
    return COL;
}
short AREF::GetROW(){
    return ROW;
}

void AREF::SetCOL(short col){
    COL=col;
}
void AREF::SetROW(short row){
    ROW=row;
}

void AREF::SetReference(std::shared_ptr<GDSIIStructure> &structure){
    _structure=structure;
}
std::shared_ptr<GDSIIStructure> AREF::GetReference(){
    return _structure;
}

void AREF::Show(){
    std::cout<<"---AREF---:\n";
    GDSIIElement::Show();
    std::cout<<"Points:\n";
    for(int i=0;i<sizeof(points)/sizeof(points[0]);i++)
    {
        std::cout<<"--["<<points[i].GetX()<<","<<points[i].GetY()<<"]\n";
    }
    std::cout<<"\nSNAME:"<<SNAME<<std::endl
             <<"COL:"<<COL<<std::endl
             <<"ROW:"<<ROW<<std::endl
             <<"MAG:"<<(HasMAG()? std::to_string(MAG):"not set")<<std::endl
             <<"ANGLE:"<<(HasANGLE()? std::to_string(ANGLE):"not set")<<std::endl;

    _structure->Show();
    std::cout<<"---END AREF---"<<std::endl;
}

void AREF::SetAngle(double angle)
{
    angleFlag=true;
    ANGLE=angle;
}

double AREF::GetAngle(){
    if(HasANGLE())
        return ANGLE;
    else{return 0;}//временно
        //throw AnError();
}

void AREF::SetMAG(double mag){
    magFlag=true;
    MAG=mag;
}

double AREF::GetMAG()
{
    if(HasMAG())
        return MAG;
    else{ return 1;}//временно
        //throw AnError();
}

bool AREF::HasANGLE()
{
    return angleFlag;
}
bool AREF::HasMAG()
{
    return magFlag;
}

std::vector<GDSIIPoint> AREF::GetPoints(){
    return points;
}
void AREF::SetPoints(const std::vector<GDSIIPoint> &points,int amount ){
    if(amount==3)//amount>0 && amount<=3)
    {
        this->points.clear();
        amountOfPoints=amount;
        for(int i=0;i<amount;i++)
            this->points.push_back(points[i]);
    }
    else
    {
        //throw AnError();
    }

}

std::string AREF::GetSNAME()
{
    return SNAME;
}

void AREF::SetSNAME(std::string name)
{
    SNAME=name;
}
