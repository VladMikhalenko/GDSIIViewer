#include "Record49_Endextn.h"

Record49_Endextn::Record49_Endextn() {
    IGDSIISource* source = SourceFactory::GetSource();
   _extension = BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4);
   recordID = ENDEXTN;
}

Record49_Endextn::Record49_Endextn(const Record49_Endextn& orig) {
    this->_extension = orig._extension;
    recordID = ENDEXTN;
}

Record49_Endextn::~Record49_Endextn() {

}

void Record49_Endextn::Show() {
    std::cout << "Record49_Endextn..." << std::endl;
    std::cout << GetExtension() << std::endl;
    std::cout << "...Record49_Endextn" << std::endl;
}

int Record49_Endextn::GetExtension() {
    return _extension;
}
