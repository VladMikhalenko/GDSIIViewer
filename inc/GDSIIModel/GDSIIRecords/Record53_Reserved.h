#pragma once
#ifndef RECORD53_RESERVED_H
#define RECORD53_RESERVED_H

#include "GDSIIRecord.h"
class Record53_Reserved :public  GDSIIRecord
{
  public:
    Record53_Reserved();
    Record53_Reserved(const Record53_Reserved& orig);
    virtual ~Record53_Reserved();
    void Show();
    int GetReserved();
  private:
    int _reserved;
};
#endif // RECORD53_RESERVED_H
