#include "Record40_Linktype.h"

Record40_Linktype::Record40_Linktype() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Info = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
}

Record40_Linktype::Record40_Linktype(const Record40_Linktype& orig) {
}

Record40_Linktype::~Record40_Linktype() {
}

void Record40_Linktype::Show() {
    std::cout<<"<Record40_Linktype..."<<std::endl;
    std::cout<<"Info: "<<_Info<<std::endl;
    std::cout<<"...Record40_Linktype>"<<std::endl;
}

short Record40_Linktype::GetInfo() {
    return _Info;
}
