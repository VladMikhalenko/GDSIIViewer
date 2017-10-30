#ifndef RECORD12_TEXT_H
#define RECORD12_TEXT_H
#include "GDSIIRecord.h"

class Record12_Text:public GDSIIRecord
{
public:
    Record12_Text();
    Record12_Text(const Record12_Text& orig);
    virtual ~Record12_Text();

    void Show();
private:

};
#endif // RECORD12_TEXT_H
