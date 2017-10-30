#include "Record54_Format.h"

Record54_Format::Record54_Format() {
    IGDSIISource* source=SourceFactory::GetSource();
    _FormatType = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = FORMAT;
}

Record54_Format::Record54_Format(const Record54_Format& orig) {
}

Record54_Format::~Record54_Format() {
}

void Record54_Format::Show() {
    std::cout<<"<Record54_Format..."<<std::endl;
    std::cout<<"Format type: "<<_FormatType<<std::endl;
    std::cout<<"...Record54_Format>"<<std::endl;
}

short Record54_Format::GetFormatType() {
    return _FormatType;
}
