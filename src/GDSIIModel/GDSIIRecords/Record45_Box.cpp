#include "Record45_Box.h"

Record45_Box::Record45_Box() {
    recordID = BOX;
}

Record45_Box::Record45_Box(const Record45_Box& orig) {
    recordID = BOX;
}

Record45_Box::~Record45_Box() {

}

void Record45_Box::Show() {
    std::cout << "Record45_Box" << std::endl;
}
