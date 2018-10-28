#include "inc/GDSIIGeometry/Primitives/GDSIIPoint.h"

GDSIIPoint::GDSIIPoint(int x, int y):_x(x),_y(y)
{}

int GDSIIPoint::GetX() const
{
    return _x;
}
int GDSIIPoint::GetY() const
{
    return _y;
}

void GDSIIPoint::SetX(int value)
{
    _x=value;
}
void GDSIIPoint::SetY(int value)
{
    _y=value;
}

GDSIIPoint GDSIIPoint::operator -(const GDSIIPoint &p)
{
    return GDSIIPoint(GetX()-p.GetX(),GetY()-p.GetY());
}
GDSIIPoint GDSIIPoint::operator +(const GDSIIPoint &p)
{
    return GDSIIPoint(GetX()+p.GetX(),GetY()+p.GetY());
}

GDSIIPoint& GDSIIPoint::operator =(const GDSIIPoint& p)
{
    this->_x=p._x;
    this->_y=p._y;
    return *this;
}
bool GDSIIPoint::operator ==(const GDSIIPoint &p)
{
    return (_x==p.GetX()) && (_y==p.GetY());
}

bool GDSIIPoint::operator !=(const GDSIIPoint &p)
{
    return !(*this == p);
}

