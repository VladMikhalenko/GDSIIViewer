#ifndef NODE_H
#define NODE_H

#include "GDSIIElement.h"

class Node:public GDSIIElement
{
    short NODETYPE;
    //Point* points;
    std::vector<GDSIIPoint> points;
public:
    Node();
    ~Node();
    void Show();

    std::vector<GDSIIPoint> GetPoints();
    void SetPoints(const std::vector<GDSIIPoint> &points, int amount);

    void SetNodeType(short n_type);
    short GetNodeType();
};

#endif // NODE_H
