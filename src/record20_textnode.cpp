#include "Record20_Textnode.h"

Record20_Textnode::Record20_Textnode() {
    recordID  = TEXTNODE;
}

Record20_Textnode::Record20_Textnode(const Record20_Textnode& orig) {
}

Record20_Textnode::~Record20_Textnode() {
}

void Record20_Textnode::Show() {
    std::cout<<"<Record20_Textnode>"<<std::endl;
}
