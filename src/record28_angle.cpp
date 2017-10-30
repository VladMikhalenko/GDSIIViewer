#include "Record28_Angle.h"

Record28_Angle::Record28_Angle() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Rotation = BinDataTypeReader::_8ByteReal(source->GetBytes(8),8);
    recordID = ANGLE;
}

Record28_Angle::Record28_Angle(const Record28_Angle& orig) {
}

Record28_Angle::~Record28_Angle() {
}

void Record28_Angle::Show() {
    std::cout<<"<Record28_Angle..."<<std::endl;
    std::cout<<"Rotation: "<<_Rotation<<std::endl;
    std::cout<<"...Record28_Angle>"<<std::endl;
}

double Record28_Angle::GetRotation() {
    return _Rotation;
}
