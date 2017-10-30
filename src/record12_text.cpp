#include "Record12_Text.h"

Record12_Text::Record12_Text() {
    recordID = TEXT;
}

Record12_Text::Record12_Text(const Record12_Text& orig) {
}

Record12_Text::~Record12_Text() {
}

void Record12_Text::Show() {
    std::cout<<"<Record12_Text>"<<std::endl;
}
