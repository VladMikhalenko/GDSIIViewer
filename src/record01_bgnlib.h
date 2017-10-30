#pragma once
#ifndef RECORD01_BGNLIB_H
#define RECORD01_BGNLIB_H
#include "GDSIIRecord.h"
//#include <ctime>

class Record01_Bgnlib:public GDSIIRecord
{
public:
    Record01_Bgnlib();
    Record01_Bgnlib(const Record01_Bgnlib& orig);
    virtual ~Record01_Bgnlib();
    void Show();
    short GetYearOfLastModificaton();
    short GetMonthOfLastModificaton();
    short GetDayOfLastModificaton();
    short GetHourOfLastModificaton();
    short GetMinuteOfLastModificaton();
    short GetSecondOfLastModificaton();

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

#endif // RECORD01_BGNLIB_H
