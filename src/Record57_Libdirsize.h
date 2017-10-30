#pragma once
#ifndef RECORD57_LIBDIRSIZE_H
#define RECORD57_LIBDIRSIZE_H

#include "GDSIIRecord.h"
class Record57_Libdirsize :public  GDSIIRecord
{
  public:
    Record57_Libdirsize();
    Record57_Libdirsize(const Record57_Libdirsize& orig);
    virtual ~Record57_Libdirsize();
    void Show();
    short GetNumberOfPages();
  private:
    short _numberOfPages;
};

#endif // RECORD57_LIBDIRSIZE_H
