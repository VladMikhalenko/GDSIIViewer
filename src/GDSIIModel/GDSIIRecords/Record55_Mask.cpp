#include "Record55_Mask.h"

Record55_Mask::Record55_Mask(int count) {
   /*_mask = "";
   char nxt;
   for(int i = 0; i < count; i++) {
       nxt = getchar();
       _mask += nxt;
   }*/
   IGDSIISource* source = SourceFactory::GetSource();
   _mask = BinDataTypeReader::_ASCIIString(source->GetBytes(count),count);
   recordID = MASK;
}

Record55_Mask::Record55_Mask(const Record55_Mask& orig) {
    this->_mask = orig._mask;
    recordID = MASK;
}

Record55_Mask::~Record55_Mask() {

}

void Record55_Mask::Show() {
    std::cout << "Record55_Mask..." << std::endl;
    std::cout << GetMask() << std::endl;
    std::cout << "...Record55_Mask" << std::endl;
}

std::string Record55_Mask::GetMask() {
    return _mask;
}
