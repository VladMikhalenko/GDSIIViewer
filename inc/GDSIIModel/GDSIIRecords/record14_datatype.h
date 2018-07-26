#ifndef RECORD14_DATATYPE_H
#define RECORD14_DATATYPE_H
#include "GDSIIRecord.h"

class Record14_Datatype:public GDSIIRecord
{
public:
    Record14_Datatype();
    virtual ~Record14_Datatype();

    void Show();
    short GetDatatype();
private:
    short _Datatype;
};
#endif // RECORD14_DATATYPE_H
