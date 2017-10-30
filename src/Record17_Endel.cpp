#include "Record17_Endel.h"

Record17_Endel::Record17_Endel() {
    recordID = ENDEL;
}

Record17_Endel::Record17_Endel(const Record17_Endel& orig) {
    recordID = ENDEL;
}

Record17_Endel::~Record17_Endel() {

}

void Record17_Endel::Show() {
    std::cout << "Record17_Endel" << std::endl;
}
