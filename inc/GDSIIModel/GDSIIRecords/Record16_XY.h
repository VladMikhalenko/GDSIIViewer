#ifndef RECORD16_XY_H
#define RECORD16_XY_H

#include "inc/GDSIIGeometry/Primitives/GDSIIPoint.h"
#include "GDSIIRecord.h"
#include <vector>
class Record16_XY :public GDSIIRecord
{
  public:
    Record16_XY(int count);
    virtual ~Record16_XY();
    void Show();
    std::vector<GDSIIPoint> GetPoints();
    int GetPointsAmount();
  private:
    std::vector<GDSIIPoint> points;
    int amountOfPoints;
};

#endif /* RECORD16_XY_H */
