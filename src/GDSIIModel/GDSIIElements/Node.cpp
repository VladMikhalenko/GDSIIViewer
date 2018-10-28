#include "inc/GDSIIModel/GDSIIElements/Node.h"

Node::Node():GDSIIElement()
{
    amountOfPoints=0;
    ID=EL_NODE;
}
Node::~Node(){

}

void Node::Show()
{
    std::cout<<"---NODE---"<<std::endl;
    GDSIIElement::Show();
    std::cout<<"Points:\n";
    for(int i=0;i<sizeof(points)/sizeof(points[0]);i++)
    {
        std::cout<<"--["<<points[i].GetX()<<","<<points[i].GetY()<<"]\n";
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

void Node::SetPoints(const std::vector<GDSIIPoint> &source,int amount){
    if(amount>=2 && amount<=50)
    {
        points.clear();
        points.reserve(amount);
        amountOfPoints=amount;
        for(int i=0;i<amount;i++)
            points.push_back(source[i]);
    }
    else
    {
        //throw AnError
    }
}
