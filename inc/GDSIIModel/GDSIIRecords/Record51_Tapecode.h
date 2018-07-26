#pragma once
#ifndef RECORD51_TAPECODE_H
#define RECORD51_TAPECODE_H

#include "GDSIIRecord.h"
class Record51_Tapecode :public  GDSIIRecord
{
  public:
    Record51_Tapecode();
    Record51_Tapecode(const Record51_Tapecode& orig);
    virtual ~Record51_Tapecode();
    void Show();
    short* GetTapeCode();
  private:
    short _tapeCode[6];
};
#endif // RECORD51_TAPECODE_H
