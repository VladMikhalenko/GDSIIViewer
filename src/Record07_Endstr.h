#pragma once
#ifndef RECORD07_ENDSTR_H
#define RECORD07_ENDSTR_H
#include "GDSIIRecord.h"

class Record07_Endstr:public GDSIIRecord
{
public:
    Record07_Endstr();
    Record07_Endstr(const Record07_Endstr& orig);
    virtual ~Record07_Endstr();
    void Show();
private:

};


#endif // RECORD07_ENDSTR_H
