#include "Record44_Propvalue.h"

Record44_Propvalue::Record44_Propvalue(int str_size) {
    IGDSIISource* source=SourceFactory::GetSource();
    _Value = BinDataTypeReader::_ASCIIString(source->GetBytes(str_size),str_size);
    recordID = PROPVALUE;
}

Record44_Propvalue::Record44_Propvalue(const Record44_Propvalue& orig) {
}

Record44_Propvalue::~Record44_Propvalue() {
}

void Record44_Propvalue::Show() {
    std::cout<<"<Record44_Propvalue..."<<std::endl;
    std::cout<<"Value: "<<_Value<<std::endl;
    std::cout<<"...Record44_Propvalue>"<<std::endl;
}

std::string Record44_Propvalue::GetValue() {
    return _Value;
}
