#ifndef SREF_H
#define SREF_H

#include "Element.h"
#include "Structure.h"

class SREF:public Element
{
    Structure* _structure;
    std::string SNAME;
    //Point* point;
    Point point;
    //strans part
    double MAG;
    double ANGLE;

    bool magFlag;
    bool angleFlag;
public:
    SREF();
    ~SREF();
    Point* GetPoints();
    void SetPoints(Point* p,int amount);

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

#endif // SREF_H
