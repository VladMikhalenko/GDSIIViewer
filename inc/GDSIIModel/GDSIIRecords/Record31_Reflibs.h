#pragma once
#ifndef RECORD31_REFLIBS_H
#define RECORD31_REFLIBS_H
#include "GDSIIRecord.h"
class Record31_Reflibs :public  GDSIIRecord
{
  public:
    Record31_Reflibs(int count);//
    Record31_Reflibs(const Record31_Reflibs& orig);
    virtual ~Record31_Reflibs();
    void Show();
    std::string GetFirstRefLib();
    std::string GetSecondRefLib();
  private:
    std::string _firstRefLib;
    std::string _secondRefLib;
};
#endif // RECORD31_REFLIBS_H
