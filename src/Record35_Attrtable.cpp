#include "Record35_Attrtable.h"
#include "GDSIISourceConsole.h"
#include "BinDataTypeReader.h"
#include <iostream>

Record35_Attrtable::Record35_Attrtable(int count) {
    /*_attr = "";
    char nxt;
    for(int i = 0; i < count; i++) {
        nxt = getchar();
        _attr += nxt;
    }*/
    IGDSIISource* source = SourceFactory::GetSource();
    _attr = BinDataTypeReader::_ASCIIString(source->GetBytes(count),count);
    recordID = ATTRTABLE;
}

Record35_Attrtable::Record35_Attrtable(const Record35_Attrtable& orig) {
    this->_attr = orig._attr;
    recordID = ATTRTABLE;
}

Record35_Attrtable::~Record35_Attrtable() {

}

void Record35_Attrtable::Show() {
    std::cout << "Record35_Attrtable..." << std::endl;
    std::cout << GetAttr() << std::endl;
    std::cout << "...Record35_Attrtable" << std::endl;
}

std::string Record35_Attrtable::GetAttr() {
    return _attr;
}
