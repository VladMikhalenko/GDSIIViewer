#include "Node.h"

Node::Node():Element()
{
    //points=0;
    amountOfPoints=0;
    ID=EL_NODE;
}
Node::~Node(){

}

void Node::Show()
{
    std::cout<<"---NODE---"<<std::endl;
    Element::Show();
    std::cout<<"Points:\n";
    for(int i=0;i<sizeof(points)/sizeof(points[0]);i++)
    {
        std::cout<<"--["<<points[i].x_coord<<","<<points[i].y_coord<<"]\n";
    }
    std::cout<<"\nNODETYPE:"<<NODETYPE<<std::endl;
    std::cout<<"---END NODE---"<<std::endl;
}

short Node::GetNodeType(){
    return NODETYPE;
}
void Node::SetNodeType(short n_type){
    NODETYPE=n_type;
}

Point* Node::GetPoints(){
    return points.data();
}
void Node::SetPoints(Point *points,int amount){
    if(amount>=2 && amount<=50)
    {
        this->points.clear();
        amountOfPoints=amount;
        for(int i=0;i<amount;i++)
            this->points.push_back(points[i]);
    }
}
