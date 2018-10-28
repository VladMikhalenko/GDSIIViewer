#ifndef GDSIILINE_H
#define GDSIILINE_H
#include "GDSIIPoint.h"

class GDSIILine
{
    GDSIIPoint _p1;
    GDSIIPoint _p2;

public:
    GDSIILine(GDSIIPoint p1, GDSIIPoint p2);
    GDSIILine(int x1=0,int y1=0,int x2=0,int y2=0);

    GDSIIPoint GetP1() const;
    GDSIIPoint GetP2() const;

    void SetP1(GDSIIPoint p);
    void SetP2(GDSIIPoint p);

    void SetPoints(GDSIIPoint p1, GDSIIPoint p2);

    bool operator ==(const GDSIILine &l) const;


};

#endif // GDSIILINE_H
