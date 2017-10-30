#ifndef RECORD44_PROPVALUE_H
#define RECORD44_PROPVALUE_H
#include "GDSIIRecord.h"
#include <string>

class Record44_Propvalue:public GDSIIRecord
{
public:
    Record44_Propvalue(int str_size);
    Record44_Propvalue(const Record44_Propvalue& orig);
    virtual ~Record44_Propvalue();

    void Show();
    std::string GetValue();
private:
    std::string _Value;
};
#endif // RECORD44_PROPVALUE_H
