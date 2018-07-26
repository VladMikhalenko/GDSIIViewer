#include "Record53_Reserved.h"

Record53_Reserved::Record53_Reserved() {
    IGDSIISource* source = SourceFactory::GetSource();
    _reserved = BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4);
    //recordID = RESERVED;
}

Record53_Reserved::Record53_Reserved(const Record53_Reserved& orig) {
    this->_reserved = orig._reserved;
    //recordID = RESERVED;
}

Record53_Reserved::~Record53_Reserved() {

}

void Record53_Reserved::Show() {
    std::cout << "Record53_Reserved..." << std::endl;
    std::cout << GetReserved() << std::endl;
    std::cout << "...Record53_Reserved" << std::endl;
}

int Record53_Reserved::GetReserved() {
    return _reserved;
}
