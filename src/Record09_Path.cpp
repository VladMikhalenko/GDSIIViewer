#include "Record09_Path.h"

Record09_Path::Record09_Path() {
    recordID = PATH;
}

Record09_Path::Record09_Path(const Record09_Path& orig) {
    recordID = PATH;
}

Record09_Path::~Record09_Path() {

}

void Record09_Path::Show() {
    std::cout << "Record09_Path" << std::endl;
}
