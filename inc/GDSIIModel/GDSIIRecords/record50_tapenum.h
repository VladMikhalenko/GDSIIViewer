#ifndef RECORD50_TAPENUM_H
#define RECORD50_TAPENUM_H
#include "GDSIIRecord.h"

class Record50_Tapenum:public GDSIIRecord
{
public:
    Record50_Tapenum();
    Record50_Tapenum(const Record50_Tapenum& orig);
    virtual ~Record50_Tapenum();

    void Show();
    short GetTapenum();
private:
    short _Tapenum;
};
#endif // RECORD50_TAPENUM_H
