#include "Record51_Tapecode.h"

Record51_Tapecode::Record51_Tapecode() {
    IGDSIISource* source = SourceFactory::GetSource();
    for (int i = 0; i < 6; i++) {
        _tapeCode[i] = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    }
    recordID = TAPECODE;
}

Record51_Tapecode::Record51_Tapecode(const Record51_Tapecode& orig) {
    for (int i = 0; i < 6; i++) {
        this->_tapeCode[i] = orig._tapeCode[i];
    }
    recordID = TAPECODE;
}

Record51_Tapecode::~Record51_Tapecode() {

}

void Record51_Tapecode::Show() {
    std::cout << "Record51_Tapecode..." << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << _tapeCode[i] << std::endl;
    }
    std::cout << "...Record51_Tapecode" << std::endl;
}

short* Record51_Tapecode::GetTapeCode() {
    return _tapeCode;
}
