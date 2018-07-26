#ifndef RECORD38_ELFLAGS_H
#define RECORD38_ELFLAGS_H
#include "GDSIIRecord.h"
#include <bitset>

class Record38_Elflags:public GDSIIRecord
{
public:
    Record38_Elflags();
    Record38_Elflags(const Record38_Elflags& orig);
    virtual ~Record38_Elflags();

    void Show();
    bool GetTemplateData();
    bool GetExternalData();
    std::bitset<16> GetElflags();
private:
    std::bitset<16> _Flags;
};
#endif // RECORD38_ELFLAGS_H
