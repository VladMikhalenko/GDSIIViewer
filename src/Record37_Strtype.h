#pragma once
#ifndef RECORD37_STRTYPE_H
#define RECORD37_STRTYPE_H

#include "GDSIIRecord.h"
class Record37_Strtype :public  GDSIIRecord
{
  public:
    Record37_Strtype();
    Record37_Strtype(const Record37_Strtype& orig);
    virtual ~Record37_Strtype();
    void Show();
    short GetStrtype();
  private:
    short _strtype;
};

#endif // RECORD37_STRTYPE_H
