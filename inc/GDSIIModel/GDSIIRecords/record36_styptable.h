#ifndef RECORD36_STYPTABLE_H
#define RECORD36_STYPTABLE_H
#include "GDSIIRecord.h"

class Record36_Styptable:public GDSIIRecord
{
public:
    Record36_Styptable();
    Record36_Styptable(const Record36_Styptable& orig);
    virtual ~Record36_Styptable();

    void Show();
    short GetInfo();
private:
    short _Info;
};
#endif // RECORD36_STYPTABLE_H
