#include "Record33_Pathtype.h"

Record33_Pathtype::Record33_Pathtype()
{
    IGDSIISource* source = SourceFactory::GetSource();
    _pathtype = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = PATHTYPE;
}

Record33_Pathtype::Record33_Pathtype(const Record33_Pathtype& orig) {
    this->_pathtype = orig._pathtype;
    recordID = PATHTYPE;
}

Record33_Pathtype::~Record33_Pathtype() {
}
void Record33_Pathtype::Show()
{
    std::cout << "<Record33_Pathtype..." << std::endl;
    std::cout << GetPathtype() << std::endl;
    std::cout << "...Record33_Pathtype>" << std::endl;
}

short Record33_Pathtype::GetPathtype()
{
    return _pathtype;
}

