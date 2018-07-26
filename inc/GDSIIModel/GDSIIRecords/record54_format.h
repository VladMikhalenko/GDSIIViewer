#ifndef RECORD54_FORMAT_H
#define RECORD54_FORMAT_H
#include "GDSIIRecord.h"

class Record54_Format:public GDSIIRecord
{
public:
    Record54_Format();
    Record54_Format(const Record54_Format& orig);
    virtual ~Record54_Format();

    void Show();
    short GetFormatType();
private:
    short _FormatType;
};
#endif // RECORD54_FORMAT_H
