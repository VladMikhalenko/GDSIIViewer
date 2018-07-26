#ifndef ELEMENT_H
#define ELEMENT_H

#include "inc/GDSIIGeometry/Primitives/GDSIIPoint.h"
#include <iostream>
#include <bitset>
#include <vector>
#include <memory>

enum ElementID{EL_UNDEFINED=-1,EL_BOUNDARY=1, EL_PATH, EL_SREF, EL_AREF, EL_TEXT, EL_BOX, EL_NODE};

class GDSIIElement
{
public:
    GDSIIElement();
    virtual ~GDSIIElement();
    virtual void Show();

    virtual  std::vector<GDSIIPoint> GetPoints()=0;
    virtual void SetPoints(const std::vector<GDSIIPoint> &points, int amount)=0;

    int GetAmountOfPoints();

    int GetLayer();
    void SetLayer(int layer);

    void SetElFlags(std::bitset<16> bitset);
    std::bitset<16> GetElFlags();

    void SetPlex(int plex);
    int GetPlex();

    bool HasELFLAGS();
    bool HasPLEX();
    bool HasProps();

    void AddPropAttr(short prop_attr);
    void AddPropValue(std::string prop_value);

    ElementID GetID();

    std::vector<short> GetPropAttr();
    std::vector<std::string> GetPropValue();

protected:
    std::bitset<16> ELFLAGS;
    int PLEX;
    int amountOfPoints;
    int _layer;
    std::vector<short> propAttributes;
    std::vector<std::string> propValues;

    bool elfFlag;
    bool plexFlag;
    bool propFlag;

    ElementID ID;

};

#endif // ELEMENT_H
