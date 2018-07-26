#ifndef RECORD27_MAG_H
#define RECORD27_MAG_H

#include "GDSIIRecord.h"
class Record27_Mag :public  GDSIIRecord
{
  public:
    Record27_Mag();
    Record27_Mag(const Record27_Mag& orig);
    virtual ~Record27_Mag();
    void Show();
    double GetMagnificationFactor();
  private:
    double _magnificationFactor;
};

#endif // RECORD27_MAG_H
