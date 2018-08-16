#ifndef GSDIIPAINTER_H
#define GSDIIPAINTER_H

#include "inc/LithographyTools/IntensityField.h"
#include "utils/Convert/GDSIIConverter.h"
class GDSIIImageBulder
{

public:
    GDSIIImageBulder();
    void IntensityFieldToJPG(const std::string &imgName, const IntensityField& field);
    void Process
};

#endif // GSDIIPAINTER_H
