#ifndef AREF_H
#define AREF_H

#include "GDSIIElement.h"
#include "inc/GDSIIModel/GDSIIStructure/Structure.h"
class AREF:public GDSIIElement
{
    std::string SNAME;
    std::shared_ptr<GDSIIStructure> _structure;

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
    void SetPoints(const std::vector<GDSIIPoint> &source, int amount);

    void SetCOL(short col);
    void SetROW(short row);

    short GetCOL();
    short GetROW();

    void SetSNAME(std::string name);
    std::string GetSNAME();

    void SetReference(std::shared_ptr<GDSIIStructure> &structure);
    std::shared_ptr<GDSIIStructure> GetReference();

    void SetMAG(double mag);
    double GetMAG();

    void SetAngle(double angle);
    double GetAngle();

    bool HasMAG();
    bool HasANGLE();

    void Show();
};

#endif // AREF_H
