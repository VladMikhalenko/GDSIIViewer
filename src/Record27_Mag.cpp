#include "Record27_Mag.h"

Record27_Mag::Record27_Mag()
{
    IGDSIISource* source = SourceFactory::GetSource();
    _magnificationFactor = BinDataTypeReader::_8ByteReal(source->GetBytes(8),8);
    recordID = MAG;
}

Record27_Mag::Record27_Mag(const Record27_Mag& orig) {
    this->_magnificationFactor = orig._magnificationFactor;
    recordID = MAG;
}

Record27_Mag::~Record27_Mag() {
}
void Record27_Mag::Show()
{
    std::cout << "<Record27_Mag..." << std::endl;
    std::cout << GetMagnificationFactor() << std::endl;
    std::cout << "...Record27_Mag>" << std::endl;
}

double Record27_Mag::GetMagnificationFactor()
{
    return _magnificationFactor;
}
