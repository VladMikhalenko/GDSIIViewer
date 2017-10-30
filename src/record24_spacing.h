#ifndef RECORD24_SPACING_H
#define RECORD24_SPACING_H
#include "GDSIIRecord.h"

class Record24_Spacing:public GDSIIRecord
{
public:
    Record24_Spacing();
    Record24_Spacing(const Record24_Spacing& orig);
    virtual ~Record24_Spacing();

    void Show();
private:

};
#endif // RECORD24_SPACING_H
