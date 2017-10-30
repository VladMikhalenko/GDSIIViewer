#pragma once
#include "Record39_Elkey.h"

Record39_Elkey::Record39_Elkey() {
    IGDSIISource* source = SourceFactory::GetSource();
    _elkey = BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4);
    //recordID = ELKEY;
}

Record39_Elkey::Record39_Elkey(const Record39_Elkey& orig) {
    this->_elkey = orig._elkey;
    //recordID = ELKEY;
}

Record39_Elkey::~Record39_Elkey() {
}
void Record39_Elkey::Show()
{
    std::cout << "<Record39_Elkey..." << std::endl;
    std::cout << GetElkey() << std::endl;
    std::cout << "...Record39_Elkey>" << std::endl;
}
int Record39_Elkey::GetElkey() {
    return _elkey;
}
