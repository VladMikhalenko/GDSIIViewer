#include "Record22_Texttype.h"

Record22_Texttype::Record22_Texttype() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Texttype = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = TEXTTYPE;
}

Record22_Texttype::Record22_Texttype(const Record22_Texttype& orig) {
}

Record22_Texttype::~Record22_Texttype() {
}

void Record22_Texttype::Show() {
    std::cout<<"<Record22_Texttype..."<<std::endl;
    std::cout<<"Text type: "<<_Texttype<<std::endl;
    std::cout<<"...Record22_Texttype>"<<std::endl;
}

short Record22_Texttype::GetTexttype() {
    return _Texttype;
}
