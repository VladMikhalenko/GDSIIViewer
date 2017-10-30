#include "Record11_Aref.h"

Record11_Aref::Record11_Aref() {
    recordID = AREF_ID;
}

Record11_Aref::Record11_Aref(const Record11_Aref& orig) {
    recordID = AREF_ID;
}

Record11_Aref::~Record11_Aref() {

}

void Record11_Aref::Show() {
    std::cout << "Record11_Aref" << std::endl;
}
