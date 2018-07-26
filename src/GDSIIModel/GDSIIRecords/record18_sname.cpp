#include "Record18_Sname.h"

Record18_Sname::Record18_Sname(int str_size) {
    IGDSIISource* source=SourceFactory::GetSource();
    _RefStructName = BinDataTypeReader::_ASCIIString(source->GetBytes(str_size),str_size);
    recordID = SNAME;
}

Record18_Sname::Record18_Sname(const Record18_Sname& orig) {
}

Record18_Sname::~Record18_Sname() {
}

void Record18_Sname::Show() {
    std::cout<<"<Record18_Sname..."<<std::endl;
    std::cout<<"Referenced structure name: "<<_RefStructName<<std::endl;
    std::cout<<"...Record18_Sname>"<<std::endl;
}

std::string Record18_Sname::GetRefStructName() {
    return _RefStructName;
}
