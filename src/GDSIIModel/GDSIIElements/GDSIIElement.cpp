#include "inc/GDSIIModel/GDSIIElements/GDSIIElement.h"

GDSIIElement::GDSIIElement():
    points(0)
   ,ELFLAGS(0)
   ,PLEX(0)
   ,amountOfPoints(0)
   ,_layer(0)
   ,propAttributes(0)
   ,propValues(0)
   ,elfFlag(false)
   ,plexFlag(false)
   ,propFlag(false)
   ,ID(EL_UNDEFINED)
{}

GDSIIElement::~GDSIIElement(){

}
int GDSIIElement::GetLayer()
{
    return _layer;
}

void GDSIIElement::SetLayer(int layer)
{
    _layer=layer;
}

void GDSIIElement::SetElFlags(std::bitset<16> bitset)
{
    elfFlag=true;
    ELFLAGS=bitset;
}
std::bitset<16> GDSIIElement::GetElFlags()
{
    return ELFLAGS;
}

void GDSIIElement::SetPlex(int plex){
    plexFlag=true;
    PLEX=plex;
}
int GDSIIElement::GetPlex()
{
    return PLEX;
}

bool GDSIIElement::HasELFLAGS()
{
    return elfFlag;
}
bool GDSIIElement::HasPLEX()
{
    return plexFlag;
}

void GDSIIElement::AddPropAttr(short prop_attr)
{
    propFlag=true;
    propAttributes.push_back(prop_attr);
}

void GDSIIElement::AddPropValue(std::string prop_value)
{
    propValues.push_back(prop_value);
}

std::vector<short> GDSIIElement::GetPropAttr()
{
    if(HasProps())
        return propAttributes;
    else return propAttributes;//throw AnError();
}

std::vector<std::string> GDSIIElement::GetPropValue()
{
    if(HasProps())
        return propValues;
    else return propValues;//throw AnError();
}

bool GDSIIElement::HasProps(){
    return propFlag;
}

void GDSIIElement::Show()
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

int GDSIIElement::GetAmountOfPoints()
{
    return amountOfPoints;
}

ElementID GDSIIElement::GetID()
{
    return this->ID;
}

std::vector<GDSIIPoint> GDSIIElement::GetPoints()
{
    return points;
}

GDSIIPoint GDSIIElement::GetPointAt(size_t index) const
{
    if(index < points.size())
    {
        return points[index];
    }
    else
    {
        throw std::out_of_range("GDSIIElement::GetPointAt() index out of range");
    }
}
