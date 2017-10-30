#ifndef AREF_H
#define AREF_H

#include "Element.h"
#include "Structure.h"
class AREF:public Element
{
    std::string SNAME;
    Structure* _structure;

    //Point* points;
    std::vector<Point> points;

    short COL;
    short ROW;

    //strans part
    double MAG;
    double ANGLE;

    bool magFlag;
    bool angleFlag;
public:
    AREF();
    ~AREF();
    Point* GetPoints();
    void SetPoints(Point* points, int amount);

    void SetCOL(short col);
    void SetROW(short row);

    short GetCOL();
    short GetROW();

    void SetSNAME(std::string name);
    std::string GetSNAME();

    void SetReference(Structure *structure);
    Structure* GetReference();

    void SetMAG(double mag);
    double GetMAG();

    void SetAngle(double angle);
    double GetAngle();

    bool HasMAG();
    bool HasANGLE();

    void Show();
};

#endif // AREF_H
