#include "Record37_Strtype.h"

Record37_Strtype::Record37_Strtype()
{
    IGDSIISource* source = SourceFactory::GetSource();
    _strtype = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    //recordID = STRTYPE;
}

Record37_Strtype::Record37_Strtype(const Record37_Strtype& orig) {
    this->_strtype = orig._strtype;
    //recordID = STRTYPE;
}

Record37_Strtype::~Record37_Strtype() {
}
void Record37_Strtype::Show()
{
    std::cout <<"<Record37_Strtype..." << std::endl;
    std::cout << GetStrtype() << std::endl;
    std::cout << "...Record37_Strtype>" << std::endl;
}

short Record37_Strtype::GetStrtype()
{
    return _strtype;
}
