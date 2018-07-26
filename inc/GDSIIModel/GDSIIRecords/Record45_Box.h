#pragma once
#ifndef RECORD45_BOX_H
#define RECORD45_BOX_H

#include "GDSIIRecord.h"

class Record45_Box :public  GDSIIRecord
{
  public:
    Record45_Box();
    Record45_Box(const Record45_Box& orig);
    virtual ~Record45_Box();
    void Show();
  private:

};


#endif // RECORD45_BOX_H
