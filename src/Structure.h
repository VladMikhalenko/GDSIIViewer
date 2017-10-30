#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Element.h"
#include <string>
#include <vector>
#include <bitset>
class Structure
{
public:
    Structure();
    ~Structure();
    void SetStructureName(std::string name);
    std::string GetStructureName();
    void SetStrClass(std::bitset<16>);
    std::bitset<16> GetStrClass();
    void AddElement(Element *element);

    int GetElementsCount();
    Element *GetElementByIndex(int index);
    void Show();
private:
    int elCount;
    std::bitset<16> STRCLASS;
    std::string STRNAME;
    std::vector<Element*> elements;
};

#endif // STRUCTURE_H
