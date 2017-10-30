#pragma once
#ifndef RECORD47_PLEX_H
#define RECORD47_PLEX_H

#include "GDSIIRecord.h"
class Record47_Plex :public  GDSIIRecord
{
  public:
    Record47_Plex();
    Record47_Plex(const Record47_Plex& orig);
    virtual ~Record47_Plex();
    void Show();
    int GetPlex();
  private:
    int _plex;
};

#endif // RECORD47_PLEX_H
