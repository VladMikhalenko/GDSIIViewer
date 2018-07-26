#ifndef RECORD21_NODE_H
#define RECORD21_NODE_H

#include "GDSIIRecord.h"
class Record21_Node :public  GDSIIRecord
{
public:
    Record21_Node();
    Record21_Node(const Record21_Node& orig);
    virtual ~Record21_Node();
    void Show();
private:

};

#endif // RECORD21_NODE_H
