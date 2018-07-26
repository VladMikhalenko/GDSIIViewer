#include "Record46_Boxtype.h"

Record46_Boxtype::Record46_Boxtype() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Boxtype = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = BOXTYPE;
}

Record46_Boxtype::Record46_Boxtype(const Record46_Boxtype& orig) {
}

Record46_Boxtype::~Record46_Boxtype() {
}

void Record46_Boxtype::Show() {
    std::cout<<"<Record46_Boxtype..."<<std::endl;
    std::cout<<"Box type: "<<_Boxtype<<std::endl;
    std::cout<<"...Record46_Boxtype>"<<std::endl;
}

short Record46_Boxtype::GetBoxtype() {
    return _Boxtype;
}
