#pragma once
#ifndef RECORD41_LINKEYS_H
#define RECORD41_LINKEYS_H

#include "GDSIIRecord.h"
class Record41_Linkeys :public  GDSIIRecord
{
  public:
    Record41_Linkeys();
    Record41_Linkeys(const Record41_Linkeys& orig);
    virtual ~Record41_Linkeys();
    void Show();
    int GetLinkeys();
  private:
    int _linkeys;
};
#endif // RECORD43_LINKEYS_H
