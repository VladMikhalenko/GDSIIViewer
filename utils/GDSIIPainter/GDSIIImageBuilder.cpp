#include "GDSIIImageBuilder.h"

GDSIIImageBulder::GDSIIImageBulder()
{

}

void GDSIIImageBulder::IntensityFieldToJPG(const std::string &imgName, const IntensityField &field)
{
    //think how to separate shooting from extraction
    QImage img = GDSIIConverter::GetInstance().Convert(field);
    img->save("[Field]"+QString(imgName)+".jpg","JPG");
}
