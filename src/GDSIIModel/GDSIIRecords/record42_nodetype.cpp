#include "Record42_Nodetype.h"

Record42_Nodetype::Record42_Nodetype() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Nodetype = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = NODETYPE;
}

Record42_Nodetype::Record42_Nodetype(const Record42_Nodetype& orig) {
}

Record42_Nodetype::~Record42_Nodetype() {
}

void Record42_Nodetype::Show() {
    std::cout<<"<Record42_Nodetype..."<<std::endl;
    std::cout<<"Node type: "<<_Nodetype<<std::endl;
    std::cout<<"...Record42_Nodetype>"<<std::endl;
}

short Record42_Nodetype::GetNodetype() {
    return _Nodetype;
}
