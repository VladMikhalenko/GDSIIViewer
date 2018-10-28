#ifndef BOX_H
#define BOX_H
#include "GDSIIElement.h"

class Box: public GDSIIElement
{
    short BOXTYPE;
public:
    Box();
    ~Box();
    void Show();

    void SetPoints(const std::vector<GDSIIPoint> &source, int amount);

    void SetBoxType(short b_type);
    short GetBoxType();
};

#endif // BOX_H
