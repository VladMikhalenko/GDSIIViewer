#pragma once
#ifndef RECORD17_ENDEL_H
#define RECORD17_ENDEL_H
#include "GDSIIRecord.h"

class Record17_Endel:public GDSIIRecord
{
public:
    Record17_Endel();
    Record17_Endel(const Record17_Endel& orig);
    virtual ~Record17_Endel();
    void Show();
private:

};

#endif // RECORD17_ENDEL_H
