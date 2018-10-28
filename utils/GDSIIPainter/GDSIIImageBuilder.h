#ifndef GSDIIPAINTER_H
#define GSDIIPAINTER_H

#include "inc/GUI/GDSIILineContainer.h"
#include "utils/Convert/GDSIIConverter.h"
class GDSIIImageBuilder
{

public:
    GDSIIImageBuilder();
    static void DrawLineContainerOnImage(QImage &image, const GDSIILineContainer& container);
    static void SaveIntensityFieldAsJpg(const IntensityField& field,const std::string& name);
};

#endif // GSDIIPAINTER_H
