#include "Element.h"

Element::Element(){
    elfFlag=false;
    plexFlag=false;
    propFlag=false;
    amountOfPoints=0;
    ID=EL_UNDEFINED;
}

Element::~Element(){

}
int Element::GetLayer()
{
    return _layer;
}

Point* Element::GetPoints()
{
    return 0;
}
void Element::SetPoints(Point *points, int amount)
{

}

void Element::SetLayer(int layer)
{
    _layer=layer;
}


void Element::SetElFlags(std::bitset<16> bitset)
{
    elfFlag=true;
    ELFLAGS=bitset;
}
std::bitset<16> Element::GetElFlags()
{
    return ELFLAGS;
}

void Element::SetPlex(int plex){
    plexFlag=true;
    PLEX=plex;
}
int Element::GetPlex()
{
    return PLEX;
}

bool Element::HasELFLAGS()
{
    return elfFlag;
}
bool Element::HasPLEX()
{
    return plexFlag;
}

void Element::AddPropAttr(short prop_attr)
{
    propFlag=true;
    propAttributes.push_back(prop_attr);
}

void Element::AddPropValue(std::string prop_value)
{
    propValues.push_back(prop_value);
}

std::vector<short> Element::GetPropAttr()
{
    if(HasProps())
        return propAttributes;
    else return propAttributes;//throw AnError();
}

std::vector<std::string> Element::GetPropValue()
{
    if(HasProps())
        return propValues;
    else return propValues;//throw AnError();
}

bool Element::HasProps(){
    return propFlag;
}

void Element::Show()
{
    std::cout<<"ELFLAGS:";
    if(elfFlag)
    {
        std::cout<<"[";
        for(int i=0;i<16;i++)
        {
            std::cout<<ELFLAGS[i]<<" ";
        }
        std::cout<<"]\n";
    }
    else
        std::cout<<"not set"<<std::endl;

    std::cout<<"PLEX:"<<(plexFlag? std::to_string(PLEX) : "not set")<<"\n"
        <<"LAYER:"<<_layer<<"\n";
    //    <<"Points:\n";
    //size of dynamic array...???
    /*for(int i=0;i<_msize(_points)/sizeof(_points[0]);i++)
    {
        std::cout<<"--["<<_points[i].x_coord<<","<<_points[i].y_coord<<"]\n";
    }*/
    std::cout<<"PROPATTR:PROPVALUE:";
    if(propFlag)
    {
        std::cout<<std::endl;
        for(int i=0;i<propAttributes.size();i++)
        {
            std::cout<<"["<<propAttributes[i]<<":"<<propValues[i]<<"\n";
        }
    }
    else
        std::cout<<"not set\n";
}

int Element::GetAmountOfPoints()
{
    return amountOfPoints;
}

ElementID Element::GetID()
{
    return this->ID;
}
