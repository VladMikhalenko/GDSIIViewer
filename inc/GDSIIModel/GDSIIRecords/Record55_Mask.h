#pragma once
#ifndef RECORD55_MASK_H
#define RECORD55_MASK_H

#include "GDSIIRecord.h"
class Record55_Mask :public  GDSIIRecord
{
  public:
    Record55_Mask(int count);
    Record55_Mask(const Record55_Mask& orig);
    virtual ~Record55_Mask();
    void Show();
    std::string GetMask();
  private:
    std::string _mask;
};

#endif // RECORD55_MASK_H
