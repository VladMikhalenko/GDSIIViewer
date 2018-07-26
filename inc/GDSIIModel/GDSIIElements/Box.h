#ifndef BOX_H
#define BOX_H
#include "GDSIIElement.h"

class Box: public GDSIIElement
{
    short BOXTYPE;
    //Point* points;
    std::vector<GDSIIPoint> points;
public:
    Box();
    ~Box();
    void Show();


    std::vector<GDSIIPoint> GetPoints();
    void SetPoints(const std::vector<GDSIIPoint> &points,int amount);

    void SetBoxType(short b_type);
    short GetBoxType();
};

#endif // BOX_H
