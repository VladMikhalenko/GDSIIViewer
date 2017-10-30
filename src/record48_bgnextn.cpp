#include "Record48_Bgnextn.h"

Record48_Bgnextn::Record48_Bgnextn() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Extension = BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4);
    recordID = BGNEXTN;
}

Record48_Bgnextn::Record48_Bgnextn(const Record48_Bgnextn& orig) {
}

Record48_Bgnextn::~Record48_Bgnextn() {
}

void Record48_Bgnextn::Show() {
    std::cout<<"<Record48_Bgnextn..."<<std::endl;
    std::cout<<"Extension: "<<_Extension<<std::endl;
    std::cout<<"...Record48_Bgnextn>"<<std::endl;
}

int Record48_Bgnextn::GetExtension() {
    return _Extension;
}
