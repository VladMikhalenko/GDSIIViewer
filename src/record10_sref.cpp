#include "Record10_Sref.h"


Record10_Sref::Record10_Sref() {
    recordID = SREF_ID;
}

Record10_Sref::Record10_Sref(const Record10_Sref& orig) {
}

Record10_Sref::~Record10_Sref() {
}

void Record10_Sref::Show() {
    std::cout<<"<Record10_Sref>"<<std::endl;
}
