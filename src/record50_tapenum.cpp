#include "Record50_Tapenum.h"

Record50_Tapenum::Record50_Tapenum() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Tapenum = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = TAPENUM;
}

Record50_Tapenum::Record50_Tapenum(const Record50_Tapenum& orig) {
}

Record50_Tapenum::~Record50_Tapenum() {
}

void Record50_Tapenum::Show() {
    std::cout<<"<Record50_Tapenum..."<<std::endl;
    std::cout<<"Tapenum: "<<_Tapenum<<std::endl;
    std::cout<<"...Record50_Tapenum>"<<std::endl;
}

short Record50_Tapenum::GetTapenum() {
    return _Tapenum;
}
