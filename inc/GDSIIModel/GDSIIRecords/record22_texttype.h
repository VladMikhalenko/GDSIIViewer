#ifndef RECORD22_TEXTTYPE_H
#define RECORD22_TEXTTYPE_H
#include "GDSIIRecord.h"

class Record22_Texttype:public GDSIIRecord
{
public:
    Record22_Texttype();
    Record22_Texttype(const Record22_Texttype& orig);
    virtual ~Record22_Texttype();

    void Show();
    short GetTexttype();
private:
    short _Texttype;
};
#endif // RECORD22_TEXTTYPE_H
