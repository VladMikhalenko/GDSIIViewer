#ifndef RECORD10_SREF_H
#define RECORD10_SREF_H
#include "GDSIIRecord.h"

class Record10_Sref:public GDSIIRecord
{
public:
    Record10_Sref();
    Record10_Sref(const Record10_Sref& orig);
    virtual ~Record10_Sref();

    void Show();
private:

};
#endif // RECORD10_SREF_H
