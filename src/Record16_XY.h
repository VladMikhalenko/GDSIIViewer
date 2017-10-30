#ifndef RECORD16_XY_H
#define RECORD16_XY_H

#include "Point.h"
#include "GDSIIRecord.h"
class Record16_XY :public GDSIIRecord
{
  public:
    Record16_XY(int count);
    Record16_XY(const Record16_XY& orig);
    virtual ~Record16_XY();
    void Show();
    Point* GetPoints();
    int GetPointsAmount();
  private:
    Point* points;
    int amountOfPoints;
};

#endif /* RECORD16_XY_H */
