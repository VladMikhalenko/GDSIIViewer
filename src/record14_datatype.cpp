#include "Record14_Datatype.h"

Record14_Datatype::Record14_Datatype() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Datatype = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = DATATYPE;
}

Record14_Datatype::Record14_Datatype(const Record14_Datatype& orig) {
}

Record14_Datatype::~Record14_Datatype() {
}

void Record14_Datatype::Show() {
    std::cout<<"<Record14_Datatype..."<<std::endl;
    std::cout<<"Data type: "<<_Datatype<<std::endl;
    std::cout<<"...Record14_Datatype>"<<std::endl;
}

short Record14_Datatype::GetDatatype() {
    return _Datatype;
}
