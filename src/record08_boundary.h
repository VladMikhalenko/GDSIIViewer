#ifndef RECORD08_BOUNDARY_H
#define RECORD08_BOUNDARY_H
#include "GDSIIRecord.h"

class Record08_Boundary:public GDSIIRecord
{
public:
    Record08_Boundary();
    Record08_Boundary(const Record08_Boundary& orig);
    virtual ~Record08_Boundary();

    void Show();
private:

};
#endif // RECORD08_BOUNDARY_H
