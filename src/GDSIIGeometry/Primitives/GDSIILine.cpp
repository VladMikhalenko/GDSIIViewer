#include "inc/GDSIIGeometry/Primitives/GDSIILine.h"

GDSIILine::GDSIILine(GDSIIPoint p1, GDSIIPoint p2):_p1(p1),_p2(p2)
{
    if(_p1.GetX() > _p2.GetX())
    {
        GDSIIPoint tmp;
        tmp = _p1;
        _p1 = _p2;
        _p2 = tmp;
    }
}
GDSIILine::GDSIILine(int x1,int y1,int x2,int y2):_p1(GDSIIPoint(x1,y1)),_p2(GDSIIPoint(x2,y2))
{}

GDSIIPoint GDSIILine::GetP1() const
{
    return _p1;
}
GDSIIPoint GDSIILine::GetP2() const
{
    return _p2;
}
void GDSIILine::SetP1(GDSIIPoint p)
{
    _p1=p;
}
void GDSIILine::SetP2(GDSIIPoint p)
{
    _p2=p;
}

bool GDSIILine::operator ==(const GDSIILine &l) const
{
    return (GetP1()==l.GetP1()) && (GetP2()==l.GetP2());
}

