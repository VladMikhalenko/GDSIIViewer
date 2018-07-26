#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "inc/GDSIIModel/GDSIIElements/GDSIIElement.h"
#include <string>
#include <vector>
#include <bitset>
#include <memory>
class GDSIIStructure
{
public:
    GDSIIStructure();
    ~GDSIIStructure();
    void SetStructureName(std::string name);
    std::string GetStructureName();
    void SetStrClass(std::bitset<16>);
    std::bitset<16> GetStrClass();
    void AddElement(std::shared_ptr<GDSIIElement> element);

    int GetElementsCount() const;
    std::shared_ptr<GDSIIElement> GetElementByIndex(size_t index) const;
    void Show();
private:
    int elCount;
    std::bitset<16> STRCLASS;
    std::string STRNAME;
    std::vector<std::shared_ptr<GDSIIElement>> elements;
};

#endif // STRUCTURE_H
