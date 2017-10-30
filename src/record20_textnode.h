#ifndef RECORD20_TEXTNODE_H
#define RECORD20_TEXTNODE_H
#include "GDSIIRecord.h"

class Record20_Textnode:public GDSIIRecord
{
public:
    Record20_Textnode();
    Record20_Textnode(const Record20_Textnode& orig);
    virtual ~Record20_Textnode();

    void Show();
private:

};
#endif // RECORD20_TEXTNODE_H
