#pragma once
#ifndef RECORD25_STRING_H
#define RECORD25_STRING_H
#include "GDSIIRecord.h"
class Record25_String :public  GDSIIRecord
{
  public:
    Record25_String(int count);
    Record25_String(const Record25_String& orig);
    virtual ~Record25_String();
    void Show();
    std::string GetContent();
  private:
    std::string _content;
};

#endif // RECORD25_STRING_H
