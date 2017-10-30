#include "Record15_Width.h"

Record15_Width::Record15_Width() {
    IGDSIISource* source=SourceFactory::GetSource();
    _width = BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4);
    recordID = WIDTH;
}

Record15_Width::Record15_Width(const Record15_Width& orig) {
    this->_width = orig._width;
    recordID = WIDTH;
}

Record15_Width::~Record15_Width() {

}

void Record15_Width::Show() {
    std::cout << "Record15_Width..." << std::endl;
    std::cout << GetWidth() << std::endl;
    std::cout << "...Record15_Width" << std::endl;
}

int Record15_Width::GetWidth() {
    return _width;
}
