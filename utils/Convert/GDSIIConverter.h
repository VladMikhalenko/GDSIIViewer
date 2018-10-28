#ifndef GDSIICONVERTER_H
#define GDSIICONVERTER_H
#include <vector>
#include <memory>

#include "QLine"
#include "QImage"

#include "inc/GDSIIGeometry/Primitives/GDSIILine.h"
#include "inc/GDSIIModel/GDSIIElements/GDSIIElement.h"
#include "inc/GDSIIModel/GDSIIElements/Boundary.h"
#include "inc/GDSIIModel/GDSIIElements/Path.h"
#include "inc/LithographyTools/IntensityField.h"

class GDSIIConverter
{

    GDSIIConverter();
    GDSIIConverter(const GDSIIConverter &con)=delete;
    GDSIIConverter& operator =(GDSIIConverter &con)=delete;
public:
    static GDSIIConverter& GetInstance()
    {
        //singleton meyers'a
        static GDSIIConverter _instance;
        return _instance;
    }

    QLine Convert(const GDSIILine &line);
    QPoint Convert(const GDSIIPoint &point);

    template<typename OutType,typename InType>
    std::vector<OutType> ConvertVector(const std::vector<InType> &v)
    {
        //rather weak realization
        std::vector<OutType> res;
        res.resize(v.size());
        for(InType item:v)
            res.emplace_back(Convert(item));
        return res;
    }

    std::shared_ptr<GDSIIElement> CopyElement(std::shared_ptr<GDSIIElement> ptr)
    {
        switch (ptr->GetID())
        {
        //пытаюсь скопировать абстрактный указатель
            case EL_BOUNDARY:
                return std::make_shared<Boundary>(*dynamic_cast<Boundary*>(ptr.get()));
            case EL_PATH:
                return std::make_shared<Path>(*dynamic_cast<Path*>(ptr.get()));
            default:
                return std::shared_ptr<GDSIIElement>(nullptr);
        }
    }
    //std::shared_ptr<QImage> Convert(const IntensityField &f);
    QImage Convert(const IntensityField &f);

};

#endif // GDSIICONVERTER_H
