#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "Element.h"

class Boundary:public Element
{
    short DATATYPE;
    //Point* points;
    std::vector<Point> points;
public:
    Boundary();
    ~Boundary();
    void Show();
    void SetDataType(short data_t);
    short GetDataType();

    Point* GetPoints();
    void SetPoints(Point* points,int amount);

};

#endif // BOUNDARY_H
