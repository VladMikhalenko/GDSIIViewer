#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "GDSIIElement.h"

class Boundary:public GDSIIElement
{
    short DATATYPE;
public:
    Boundary();
    ~Boundary();
    void Show();
    void SetDataType(short data_t);
    short GetDataType();

    void SetPoints(const std::vector<GDSIIPoint> &source, int amount);

};

#endif // BOUNDARY_H
