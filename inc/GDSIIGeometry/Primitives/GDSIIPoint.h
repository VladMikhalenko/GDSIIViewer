#ifndef GDSIIPOINT_H
#define GDSIIPOINT_H


class GDSIIPoint
{
    int _x;
    int _y;
public:
    GDSIIPoint(int x=0,int y=0);
    int GetX() const;
    int GetY() const;
    void SetX(int value);
    void SetY(int value);

    GDSIIPoint operator - (const GDSIIPoint &p);
    GDSIIPoint operator + (const GDSIIPoint &p);
    bool operator == (const GDSIIPoint &p);
    bool operator != (const GDSIIPoint &p);


};

#endif // GDSIIPOINT_H
