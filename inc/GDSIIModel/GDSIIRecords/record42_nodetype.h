#ifndef RECORD42_NODETYPE_H
#define RECORD42_NODETYPE_H
#include "GDSIIRecord.h"

class Record42_Nodetype:public GDSIIRecord
{
public:
    Record42_Nodetype();
    Record42_Nodetype(const Record42_Nodetype& orig);
    virtual ~Record42_Nodetype();

    void Show();
    short GetNodetype();
private:
    short _Nodetype;
};
#endif // RECORD42_NODETYPE_H
