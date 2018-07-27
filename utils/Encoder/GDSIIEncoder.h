#ifndef GDSIIENCODER_H
#define GDSIIENCODER_H

#include "inc/GUI/GDSIILineContainer.h"
#include "inc/LithographyTools/LineAnalyzer.h"
#include <memory>
#include <map>

#define ENCODE_TWO_IN_INT32(left,right)  ((left<<16)|(right))
#define ENCODE_LEFT_IN_INT32(base,value) ((base&65280)|(value<<16))
#define ENCODE_RIGHT_IN_INT32(base,value)((base&255)|(value))
class GDSIIEncoder
{
    LineAnalyzer lineAnalizer;
    std::map<int,int> locMap;
    void SortContainer(GDSIILineContainer &cont);
public:
    GDSIIEncoder();
    void Encode(std::string fileName, GDSIILineContainer &cont);
    void ConstructMap(const GDSIILineContainer &cont);
};

#endif // GDSIIENCODER_H
