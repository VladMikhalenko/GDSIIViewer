#ifndef RECORD46_BOXTYPE_H
#define RECORD46_BOXTYPE_H
#include "GDSIIRecord.h"

class Record46_Boxtype:public GDSIIRecord
{
public:
    Record46_Boxtype();
    Record46_Boxtype(const Record46_Boxtype& orig);
    virtual ~Record46_Boxtype();

    void Show();
    short GetBoxtype();
private:
    short _Boxtype;
};
#endif // RECORD46_BOXTYPE_H
