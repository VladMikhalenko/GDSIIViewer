#ifndef RECORD28_ANGLE_H
#define RECORD28_ANGLE_H
#include "GDSIIRecord.h"

class Record28_Angle:public GDSIIRecord
{
public:
    Record28_Angle();
    Record28_Angle(const Record28_Angle& orig);
    virtual ~Record28_Angle();

    void Show();
    double GetRotation();
private:
    double _Rotation;
};
#endif // RECORD28_ANGLE_H
