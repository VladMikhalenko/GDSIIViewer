#include "Record21_Node.h"

Record21_Node::Record21_Node() {
    recordID = NODE;
}

Record21_Node::Record21_Node(const Record21_Node& orig) {
    recordID = NODE;
}

Record21_Node::~Record21_Node() {

}

void Record21_Node::Show() {
    std::cout << "Record21_Node" << std::endl;
}
