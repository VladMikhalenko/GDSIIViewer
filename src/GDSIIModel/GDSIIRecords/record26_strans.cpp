#include "Record26_Strans.h"

Record26_Strans::Record26_Strans() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Trans = BinDataTypeReader::_BitArray(source->GetBytes(2),2);
    recordID = STRANS;
}

Record26_Strans::Record26_Strans(const Record26_Strans& orig) {
}

Record26_Strans::~Record26_Strans() {
}

void Record26_Strans::Show() {
    std::cout<<"<Record26_Strans..."<<std::endl;
    std::cout<<"Reflection: "<<GetReflection()<<std::endl;
    std::cout<<"Magnification: "<<GetMagnification()<<std::endl;
    std::cout<<"Angle: "<<GetAngle()<<std::endl;
    std::cout<<"...Record26_Strans>"<<std::endl;
}

bool Record26_Strans::GetReflection() {
    return _Trans[15];
}

bool Record26_Strans::GetMagnification() {
    return _Trans[2];
}

bool Record26_Strans::GetAngle() {
    return _Trans[1];
}
