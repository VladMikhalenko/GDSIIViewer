#ifndef RECORD52_STRCLASS_H
#define RECORD52_STRCLASS_H
#include "GDSIIRecord.h"
#include <bitset>

class Record52_Strclass:public GDSIIRecord
{
public:
    Record52_Strclass();
    Record52_Strclass(const Record52_Strclass& orig);
    virtual ~Record52_Strclass();

    void Show();
    std::bitset<16> GetInfo();
private:
    std::bitset<16> _Info;
};
#endif // RECORD52_STRCLASS_H
