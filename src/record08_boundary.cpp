#include "Record08_Boundary.h"


Record08_Boundary::Record08_Boundary() {
    recordID = BOUNDARY;
}

Record08_Boundary::Record08_Boundary(const Record08_Boundary& orig) {
}

Record08_Boundary::~Record08_Boundary() {
}

void Record08_Boundary::Show() {
    std::cout<<"<Record08_Boundary>"<<std::endl;
}
