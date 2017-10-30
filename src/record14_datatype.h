#ifndef RECORD14_DATATYPE_H
#define RECORD14_DATATYPE_H
#include "GDSIIRecord.h"

class Record14_Datatype:public GDSIIRecord
{
public:
    Record14_Datatype();
    Record14_Datatype(const Record14_Datatype& orig);
    virtual ~Record14_Datatype();

    void Show();
    short GetDatatype();
private:
    short _Datatype;
};
#endif // RECORD14_DATATYPE_H
