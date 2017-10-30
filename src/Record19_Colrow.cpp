#include "Record19_Colrow.h"

Record19_Colrow::Record19_Colrow() {
    IGDSIISource* source=SourceFactory::GetSource();
    _colnum = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _rownum = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = COLROW;
}

Record19_Colrow::Record19_Colrow(const Record19_Colrow& orig) {
    this->_colnum = orig._colnum;
    this->_rownum = orig._rownum;
    recordID = COLROW;
}

Record19_Colrow::~Record19_Colrow() {

}

void Record19_Colrow::Show() {
    std::cout << "Record19_Colrow..." << std::endl;
    std::cout << GetColnum() << std::endl;
    std::cout << GetRownum() << std::endl;
    std::cout << "...Record19_Colrow" << std::endl;
}

short Record19_Colrow::GetColnum() {
    return _colnum;
}

short Record19_Colrow::GetRownum() {
    return _rownum;
}
