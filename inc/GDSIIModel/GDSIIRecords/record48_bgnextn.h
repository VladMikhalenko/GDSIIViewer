#ifndef RECORD48_BGNEXTN_H
#define RECORD48_BGNEXTN_H
#include "GDSIIRecord.h"

class Record48_Bgnextn:public GDSIIRecord
{
public:
    Record48_Bgnextn();
    Record48_Bgnextn(const Record48_Bgnextn& orig);
    virtual ~Record48_Bgnextn();

    void Show();
    int GetExtension();
private:
    int _Extension;
};
#endif // RECORD48_BGNEXTN_H
