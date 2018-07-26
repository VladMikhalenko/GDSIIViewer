#include "inc/GDSIIModel/GDSIIRecords/Record07_Endstr.h"

Record07_Endstr::Record07_Endstr()
{
    recordID=ENDSTR;
}

Record07_Endstr::~Record07_Endstr() {

}

void Record07_Endstr::Show() {
    std::cout << "Record07_Endstr" << std::endl;
}
