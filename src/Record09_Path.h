#pragma once
#ifndef RECORD09_PATH_H
#define RECORD09_PATH_H
#include "GDSIIRecord.h"

class Record09_Path:public GDSIIRecord
{
public:
    Record09_Path();
    Record09_Path(const Record09_Path& orig);
    virtual ~Record09_Path();
    void Show();
private:

};

#endif // RECORD09_PATH_H
