#ifndef BOX_H
#define BOX_H
#include "Element.h"

class Box: public Element
{
    short BOXTYPE;
    //Point* points;
    std::vector<Point> points;
public:
    Box();
    ~Box();
    void Show();


     Point* GetPoints();
    void SetPoints(Point *points,int amount);

    void SetBoxType(short b_type);
    short GetBoxType();
};

#endif // BOX_H
