#pragma once
#ifndef RECORD15_WIDTH_H
#define RECORD15_WIDTH_H
#include "GDSIIRecord.h"

class Record15_Width:public GDSIIRecord
{
public:
    Record15_Width();
    virtual ~Record15_Width();
    void Show();
    int GetWidth();
private:
    int _width;
};

#endif // RECORD15_WIDTH_H
