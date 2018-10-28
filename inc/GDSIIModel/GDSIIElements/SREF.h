#ifndef SREF_H
#define SREF_H

#include "GDSIIElement.h"
#include "inc/GDSIIModel/GDSIIStructure/Structure.h"

class SREF:public GDSIIElement
{
    std::shared_ptr<GDSIIStructure> _structure;
    std::string SNAME;
    //strans part
    double MAG;
    double ANGLE;

    bool magFlag;
    bool angleFlag;
public:
    SREF();
    ~SREF();
    void SetPoints(const std::vector<GDSIIPoint> &source, int amount);

    void SetSNAME(std::string name);
    std::string GetSNAME();

    void SetReference(std::shared_ptr<GDSIIStructure> structure);
    std::shared_ptr<GDSIIStructure> GetReference();

    void SetMAG(double mag);
    double GetMAG();

    void SetAngle(double angle);
    double GetAngle();

    bool HasMAG();
    bool HasANGLE();

    void Show();
};

#endif // SREF_H
