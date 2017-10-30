#include "Record43_Propattr.h"

Record43_Propattr::Record43_Propattr() {
    IGDSIISource* source = SourceFactory::GetSource();
    _attributeNumber = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = PROPATTR;
}

Record43_Propattr::Record43_Propattr(const Record43_Propattr& orig) {

}

Record43_Propattr::~Record43_Propattr() {

}

void Record43_Propattr::Show() {
    std::cout << "Record43_Propattr..." << std::endl;
    std::cout << GetAttributeNumber() << std::endl;
    std::cout << "...Record43_Propattr" << std::endl;
}

short Record43_Propattr::GetAttributeNumber() {
    return _attributeNumber;
}
