#pragma once
#ifndef RECORD33_PATHTYPE_H
#define RECORD33_PATHTYPE_H

#include "GDSIIRecord.h"
class Record33_Pathtype :public  GDSIIRecord
{
  public:
    Record33_Pathtype();
    Record33_Pathtype(const Record33_Pathtype& orig);
    virtual ~Record33_Pathtype();
    void Show();
    short GetPathtype();
  private:
    short _pathtype;
};

#endif // RECORD33_PATHTYPE_H
