#pragma once
#ifndef RECORD03_UNITS_H
#define RECORD03_UNITS_H
#include "GDSIIRecord.h"

class Record03_Units:public GDSIIRecord
{
public:
    Record03_Units();
    Record03_Units(const Record03_Units& orig);
    virtual ~Record03_Units();
    void Show();
    double GetSizeInUserUnits();
    double GetSizeInMeters();
private:
    double _sizeInUserUnits;
    double _sizeInMeters;
};
#endif // RECORD03_UNITS_H
