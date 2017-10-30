#include "Record02_Libname.h"

Record02_Libname::Record02_Libname(int str_size) {
    IGDSIISource* source=SourceFactory::GetSource();
    _LibraryName = BinDataTypeReader::_ASCIIString(source->GetBytes(str_size),str_size);
    recordID = LIBNAME;
}

Record02_Libname::Record02_Libname(const Record02_Libname& orig) {
}

Record02_Libname::~Record02_Libname() {
}

void Record02_Libname::Show() {
    std::cout<<"<Record02_Libname..."<<std::endl;
    std::cout<<"Library name: "<<_LibraryName<<std::endl;
    std::cout<<"...Record02_Libname>"<<std::endl;
}

std::string Record02_Libname::GetLibraryName() {
    return _LibraryName;
}
