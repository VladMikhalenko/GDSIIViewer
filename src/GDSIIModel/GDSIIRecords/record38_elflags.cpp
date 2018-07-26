#include "Record38_Elflags.h"

Record38_Elflags::Record38_Elflags() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Flags = BinDataTypeReader::_BitArray(source->GetBytes(2),2);
    recordID = ELFLAGS;
}

Record38_Elflags::Record38_Elflags(const Record38_Elflags& orig) {
}

Record38_Elflags::~Record38_Elflags() {
}

void Record38_Elflags::Show() {
    std::cout<<"<Record38_Elflags..."<<std::endl;
    std::cout<<"Template data: "<<GetTemplateData()<<std::endl;
    std::cout<<"External data: "<<GetExternalData()<<std::endl;
    std::cout<<"...Record38_Elflags>"<<std::endl;
}

bool Record38_Elflags::GetTemplateData() {
    return _Flags[0];
}

bool Record38_Elflags::GetExternalData() {
    return _Flags[1];
}

std::bitset<16> Record38_Elflags::GetElflags()
{
    return _Flags;
}
