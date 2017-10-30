#pragma once
#ifndef RECORD23_PRESENTATION_H
#define RECORD23_PRESENTATION_H
//#include <bitset>

#include "GDSIIRecord.h"
class Record23_Presentation :public  GDSIIRecord
{
  public:
    Record23_Presentation();
    Record23_Presentation(const Record23_Presentation& orig);
    virtual ~Record23_Presentation();
    void Show();
    short GetFont();
    short GetVerticalPresentation();
    short GetHorizontalPresentation();
  private:
    std::bitset<16> _presentation;
};

#endif // RECORD23_PRESENTATION_H
