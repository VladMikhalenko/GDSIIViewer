#pragma once
#ifndef RECORD43_PROPATTR_H
#define RECORD43_PROPATTR_H
#include "GDSIIRecord.h"

class Record43_Propattr :public  GDSIIRecord
{
  public:
    Record43_Propattr();
    Record43_Propattr(const Record43_Propattr& orig);
    virtual ~Record43_Propattr();
    void Show();
    short GetAttributeNumber();
  private:
    short _attributeNumber;
};

#endif // RECORD43_PROPATTR_H
