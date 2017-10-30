#ifndef RECORD04_ENDLIB_H
#define RECORD04_ENDLIB_H
#include "GDSIIRecord.h"

class Record04_Endlib:public GDSIIRecord
{
public:
    Record04_Endlib();
    Record04_Endlib(const Record04_Endlib& orig);
    virtual ~Record04_Endlib();

    void Show();
private:

};
#endif // RECORD04_ENDLIB_H
