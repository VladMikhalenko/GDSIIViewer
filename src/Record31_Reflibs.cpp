#include "Record31_Reflibs.h"

Record31_Reflibs::Record31_Reflibs(int count) {
    /*_refLibs = "";
    char nxt;
    for(int i = 0; i < count; i++) {
        nxt = getchar();
        _refLibs += nxt;
    }*/
    IGDSIISource* source = SourceFactory::GetSource();
    _firstRefLib = BinDataTypeReader::_ASCIIString(source->GetBytes(45),45);
    _secondRefLib = BinDataTypeReader::_ASCIIString(source->GetBytes(count-45),count-45);
    recordID = REFLIBS;
}

Record31_Reflibs::Record31_Reflibs(const Record31_Reflibs& orig) {
    this->_firstRefLib = orig._firstRefLib;
    this->_secondRefLib = orig._secondRefLib;
    recordID = REFLIBS;
}

Record31_Reflibs::~Record31_Reflibs() {

}

void Record31_Reflibs::Show() {
    std::cout << "Record31_Reflibs..." << std::endl;
    std::cout << GetFirstRefLib() << std::endl;
    std::cout << GetSecondRefLib() << std::endl;
    std::cout << "...Record31_Reflibs" << std::endl;
}

std::string Record31_Reflibs::GetFirstRefLib() {
    return _firstRefLib;
}

std::string Record31_Reflibs::GetSecondRefLib() {
    return _secondRefLib;
}
