#pragma once
#ifndef RECORD49_ENDEXTN_H
#define RECORD49_ENDEXTN_H
#include "GDSIIRecord.h"

class Record49_Endextn :public  GDSIIRecord
{
  public:
    Record49_Endextn();
    Record49_Endextn(const Record49_Endextn& orig);
    virtual ~Record49_Endextn();
    void Show();
    int GetExtension();
  private:
    int _extension;
};

#endif // RECORD49_ENDEXTN_H
