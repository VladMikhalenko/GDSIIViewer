#include "Record06_Strname.h"


Record06_Strname::Record06_Strname(int str_size) {
    IGDSIISource* source=SourceFactory::GetSource();
    _StructureName = BinDataTypeReader::_ASCIIString(source->GetBytes(str_size),str_size);
    recordID = STRNAME;
}

Record06_Strname::Record06_Strname(const Record06_Strname& orig) {
}

Record06_Strname::~Record06_Strname() {
}

void Record06_Strname::Show() {
    std::cout<<"<Record06_Strname..."<<std::endl;
    std::cout<<"Structure name: "<<_StructureName<<std::endl;
    std::cout<<"...Record06_Strname>"<<std::endl;
}

std::string Record06_Strname::GetStructureName() {
    return _StructureName;
}
