#ifndef RECORD40_LINKTYPE_H
#define RECORD40_LINKTYPE_H
#include "GDSIIRecord.h"

class Record40_Linktype:public GDSIIRecord
{
public:
    Record40_Linktype();
    Record40_Linktype(const Record40_Linktype& orig);
    virtual ~Record40_Linktype();

    void Show();
    short GetInfo();
private:
    short _Info;
};
#endif // RECORD40_LINKTYPE_H
