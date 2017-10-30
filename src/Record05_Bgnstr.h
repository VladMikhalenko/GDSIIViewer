#pragma once
#ifndef RECORD05_BGNSTR_H
#define RECORD05_BGNSTR_H
#include "GDSIIRecord.h"

class Record05_Bgnstr:public GDSIIRecord
{
public:
    Record05_Bgnstr();
    Record05_Bgnstr(const Record05_Bgnstr& orig);
    virtual ~Record05_Bgnstr();
    void Show();

    short GetYearOfLastModification();
    short GetMonthOfLastModification();
    short GetDayOfLastModification();
    short GetHourOfLastModification();
    short GetMinuteOfLastModification();
    short GetSecondOfLastModification();

    short GetYearOfLastAccess();
    short GetMonthOfLastAccess();
    short GetDayOfLastAccess();
    short GetHourOfLastAccess();
    short GetMinuteOfLastAccess();
    short GetSecondOfLastAccess();

private:
    short _yearOfLastModification;
    short _monthOfLastModification;
    short _dayOfLastModification;
    short _hourOfLastModification;
    short _minuteOfLastModification;
    short _secondOfLastModification;

    short _yearOfLastAccess;
    short _monthOfLastAccess;
    short _dayOfLastAccess;
    short _hourOfLastAccess;
    short _minuteOfLastAccess;
    short _secondOfLastAccess;
};

#endif // RECORD05_BGNSTR_H
