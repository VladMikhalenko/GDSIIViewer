#include "Record58_Srfname.h"

Record58_Srfname::Record58_Srfname(int str_size) {
    IGDSIISource* source=SourceFactory::GetSource();
    _SRFName = BinDataTypeReader::_ASCIIString(source->GetBytes(str_size),str_size);
    recordID = SRFNAME;
}

Record58_Srfname::Record58_Srfname(const Record58_Srfname& orig) {
}

Record58_Srfname::~Record58_Srfname() {
}

void Record58_Srfname::Show() {
    std::cout<<"<Record58_Srfname..."<<std::endl;
    std::cout<<"Sticks Rules File name: "<<_SRFName<<std::endl;
    std::cout<<"...Record58_Srfname>"<<std::endl;
}

std::string Record58_Srfname::GetSRFName() {
    return _SRFName;
}
