#pragma once
#ifndef RECORD19_COLROW_H
#define RECORD19_COLROW_H
#include "GDSIIRecord.h"

class Record19_Colrow:public GDSIIRecord
{
public:
    Record19_Colrow();
    Record19_Colrow(const Record19_Colrow& orig);
    virtual ~Record19_Colrow();
    void Show();
    short GetColnum();
    short GetRownum();
private:
    short _colnum;
    short _rownum;
};

#endif // RECORD19_COLROW_H
