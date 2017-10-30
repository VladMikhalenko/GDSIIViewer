#pragma once
#ifndef RECORD13_LAYER_H
#define RECORD13_LAYER_H
#include "GDSIIRecord.h"

class Record13_Layer:public GDSIIRecord
{
public:
    Record13_Layer();
    Record13_Layer(const Record13_Layer& orig);
    virtual ~Record13_Layer();
    void Show();
    short GetLayer();
private:
    short _layer;
};

#endif // RECORD13_LAYER_H
