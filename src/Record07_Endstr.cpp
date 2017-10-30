#include "Record07_Endstr.h"

Record07_Endstr::Record07_Endstr() {
    recordID = ENDSTR;
}

Record07_Endstr::Record07_Endstr(const Record07_Endstr& orig) {
    recordID = ENDSTR;
}

Record07_Endstr::~Record07_Endstr() {

}

void Record07_Endstr::Show() {
    std::cout << "Record07_Endstr" << std::endl;
}
