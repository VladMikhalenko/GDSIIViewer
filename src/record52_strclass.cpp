#include "Record52_Strclass.h"

Record52_Strclass::Record52_Strclass() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Info = BinDataTypeReader::_BitArray(source->GetBytes(2),2);
    recordID = STRCLASS;
}

Record52_Strclass::Record52_Strclass(const Record52_Strclass& orig) {
}

Record52_Strclass::~Record52_Strclass() {
}

void Record52_Strclass::Show() {
    std::cout<<"<Record38_Elflags..."<<std::endl;
    for (int i = 0; i < 16; i++) {
        cout<<"Bit #"<<i<<": "<<_Info[i]<<endl;
    }
    std::cout<<"...Record38_Elflags>"<<std::endl;
}

std::bitset<16> Record52_Strclass::GetInfo() {
    return _Info;
}
