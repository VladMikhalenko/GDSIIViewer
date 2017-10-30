#include "Record41_Linkeys.h"

Record41_Linkeys::Record41_Linkeys() {
    IGDSIISource* source = SourceFactory::GetSource();
    _linkeys = BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4);
    //recordID = LINKEYS;
}

Record41_Linkeys::Record41_Linkeys(const Record41_Linkeys& orig) {
    this->_linkeys = orig._linkeys;
    //recordID = LINKEYS;
}

Record41_Linkeys::~Record41_Linkeys() {

}

void Record41_Linkeys::Show() {
    std::cout << "Record41_Linkeys..."<< std::endl;
    std::cout <<  GetLinkeys() << std::endl;
    std::cout << "...Record41_Linkeys" << std::endl;
}

int Record41_Linkeys::GetLinkeys() {
    return _linkeys;
}
