#include "Record36_Styptable.h"

Record36_Styptable::Record36_Styptable() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Info = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
}

Record36_Styptable::Record36_Styptable(const Record36_Styptable& orig) {
}

Record36_Styptable::~Record36_Styptable() {
}

void Record36_Styptable::Show() {
    std::cout<<"<Record36_Styptable..."<<std::endl;
    std::cout<<"Info: "<<_Info<<std::endl;
    std::cout<<"...Record36_Styptable>"<<std::endl;
}

short Record36_Styptable::GetInfo() {
    return _Info;
}
