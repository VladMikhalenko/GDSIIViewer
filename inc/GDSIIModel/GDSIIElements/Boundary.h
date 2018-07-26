#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "GDSIIElement.h"

class Boundary:public GDSIIElement
{
    short DATATYPE;
    //Point* points;
    std::vector<GDSIIPoint> points;
public:
    Boundary();
    ~Boundary();
    void Show();
    void SetDataType(short data_t);
    short GetDataType();

    std::vector<GDSIIPoint> GetPoints();
    void SetPoints(const std::vector<GDSIIPoint> &points, int amount);

};

#endif // BOUNDARY_H
