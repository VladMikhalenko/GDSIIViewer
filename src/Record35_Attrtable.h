#pragma once
#ifndef RECORD35_ATTRTABLE_H
#define RECORD35_ATTRTABLE_H
#include "GDSIIRecord.h"

class Record35_Attrtable :public  GDSIIRecord
{
  public:
    Record35_Attrtable(int count);
    Record35_Attrtable(const Record35_Attrtable& orig);
    virtual ~Record35_Attrtable();
    void Show();
    std::string GetAttr();
  private:
    std::string _attr;
};

#endif // RECORD35_ATTRTABLE_H
