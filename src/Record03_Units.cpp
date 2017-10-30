#include "Record03_Units.h"

Record03_Units::Record03_Units() {
    IGDSIISource* source=SourceFactory::GetSource();
    _sizeInUserUnits = BinDataTypeReader::_8ByteReal(source->GetBytes(8),8);
    _sizeInMeters = BinDataTypeReader::_8ByteReal(source->GetBytes(8),8);
    recordID = UNITS;
}

Record03_Units::Record03_Units(const Record03_Units& orig) {
    this -> _sizeInUserUnits = orig._sizeInUserUnits;
    this -> _sizeInMeters = orig._sizeInMeters;
    recordID = UNITS;
}

void Record03_Units::Show() {
    std::cout << "Record03_Units..." << std::endl;
    std::cout << GetSizeInUserUnits() << std::endl;
    std::cout << GetSizeInMeters() << std::endl;
    std::cout << "...Record03_Units" << std::endl;
}

Record03_Units::~Record03_Units() {

}

double Record03_Units::GetSizeInUserUnits() {
    return _sizeInUserUnits;
}

double Record03_Units::GetSizeInMeters() {
    return _sizeInMeters;
}
