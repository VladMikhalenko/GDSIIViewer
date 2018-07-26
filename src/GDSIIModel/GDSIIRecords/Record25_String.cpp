#include "Record25_String.h"

Record25_String::Record25_String(int count) {
    /*_content = "";
    char nxt;
    for(int i = 0; i < count; i++) {
        nxt = getchar();
        _content += nxt;
    }*/
    IGDSIISource* source = SourceFactory::GetSource();
    _content = BinDataTypeReader::_ASCIIString(source->GetBytes(count),count);
    recordID = STRING;
}

Record25_String::Record25_String(const Record25_String& orig) {
    this->_content = orig._content;
    recordID = STRING;
}

Record25_String::~Record25_String() {

}

void Record25_String::Show() {
    std::cout << "Record25_String..." << std::endl;
    std::cout << GetContent() << std::endl;
    std::cout << "...Record25_String" << std::endl;
}

std::string Record25_String::GetContent() {
    return _content;
}
