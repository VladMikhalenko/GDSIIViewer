#include "inc/GDSIIModel/GDSIIStructure/Structure.h"
#include <iostream>
GDSIIStructure::GDSIIStructure():elCount(0),elements(0)
{}

GDSIIStructure::~GDSIIStructure()
{

}

void GDSIIStructure::SetStructureName(std::string name)
{
    STRNAME=name;
}

std::string GDSIIStructure::GetStructureName()
{
    return STRNAME;
}

void GDSIIStructure::AddElement(std::shared_ptr<GDSIIElement> element)
{
    elCount++;
    elements.push_back(element);
}

void GDSIIStructure::SetStrClass(std::bitset<16> bitset)
{
    STRCLASS=bitset;
}

std::bitset<16> GDSIIStructure::GetStrClass()
{
    return STRCLASS;
}

void GDSIIStructure::Show(){
    std::cout<<"STRUCTURE '"<<STRNAME<<"':\n";
    for(int i=0;i<elements.size();i++)
    {
        elements[i]->Show();
    }
    std::cout<<"END STRUCTURE '"<<STRNAME<<"'\n";
}

int GDSIIStructure::GetElementsCount() const
{
    return elCount;//elements.size();
}

std::shared_ptr<GDSIIElement> GDSIIStructure::GetElementByIndex(size_t index) const
{
    if(index<GetElementsCount())
        return elements[index];
    return std::shared_ptr<GDSIIElement>();
    //return std::make_shared<GDSIIElement>(nullptr);//throw AnError();
}
