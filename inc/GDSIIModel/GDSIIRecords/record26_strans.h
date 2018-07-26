#ifndef RECORD26_STRANS_H
#define RECORD26_STRANS_H
#include "GDSIIRecord.h"
#include <bitset>

class Record26_Strans:public GDSIIRecord
{
public:
    Record26_Strans();
    Record26_Strans(const Record26_Strans& orig);
    virtual ~Record26_Strans();

    void Show();
    bool GetReflection();
    bool GetMagnification();
    bool GetAngle();
private:
    std::bitset<16> _Trans;
};
#endif // RECORD26_STRANS_H
