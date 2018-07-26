#include "Record57_Libdirsize.h"

Record57_Libdirsize::Record57_Libdirsize() {
    IGDSIISource* source = SourceFactory::GetSource();
    _numberOfPages = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = LIBDIRSIZE;
}

Record57_Libdirsize::Record57_Libdirsize(const Record57_Libdirsize& orig) {
    this->_numberOfPages = orig._numberOfPages;
}

Record57_Libdirsize::~Record57_Libdirsize() {

}

void Record57_Libdirsize::Show() {
    std::cout << "Record57_Libdirsize..." << std::endl;
    std::cout << GetNumberOfPages() << std::endl;
    std::cout << "...Record57_Libdirsize" << std::endl;
}

short Record57_Libdirsize::GetNumberOfPages() {
    return _numberOfPages;
}
