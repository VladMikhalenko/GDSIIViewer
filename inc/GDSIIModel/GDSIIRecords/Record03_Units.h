#pragma once
#ifndef RECORD03_UNITS_H
#define RECORD03_UNITS_H
#include "GDSIIRecord.h"

class Record03_Units:public GDSIIRecord
{
public:
    Record03_Units();
    virtual ~Record03_Units();
    void Show();
    double GetSizeInUserUnits();
    double GetSizeInMeters();
private:
    double _sizeInUserUnits;
    double _sizeInMeters;
};
#endif // RECORD03_UNITS_H
