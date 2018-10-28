#ifndef NODE_H
#define NODE_H

#include "GDSIIElement.h"

class Node:public GDSIIElement
{
    short NODETYPE;
public:
    Node();
    ~Node();
    void Show();

    void SetPoints(const std::vector<GDSIIPoint> &source, int amount);

    void SetNodeType(short n_type);
    short GetNodeType();
};

#endif // NODE_H
