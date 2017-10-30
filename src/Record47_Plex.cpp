#include "Record47_Plex.h"

Record47_Plex::Record47_Plex() {
    IGDSIISource* source = SourceFactory::GetSource();
    _plex = BinDataTypeReader::_4ByteInteger(source->GetBytes(4),4);
    recordID = PLEX;
}

Record47_Plex::Record47_Plex(const Record47_Plex& orig) {
    this->_plex = orig._plex;
    recordID = PLEX;
}

Record47_Plex::~Record47_Plex() {

}

void Record47_Plex::Show() {
    std::cout << "Record47_Plex..." << std::endl;
    std::cout << GetPlex() << std::endl;
    std::cout << "...Record47_Plex" << std::endl;
}

int Record47_Plex::GetPlex() {
    return _plex;
}
