#pragma once
#ifndef RECORD11_AREF_H
#define RECORD11_AREF_H
#include "GDSIIRecord.h"

class Record11_Aref:public GDSIIRecord
{
public:
    Record11_Aref();
    Record11_Aref(const Record11_Aref& orig);
    virtual ~Record11_Aref();
    void Show();
private:

};

#endif // RECORD11_AREF_H
