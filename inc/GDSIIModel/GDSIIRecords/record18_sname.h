#ifndef RECORD18_SNAME_H
#define RECORD18_SNAME_H
#include "GDSIIRecord.h"
#include <string>

class Record18_Sname:public GDSIIRecord
{
public:
    Record18_Sname(int str_size);
    Record18_Sname(const Record18_Sname& orig);
    virtual ~Record18_Sname();

    void Show();
    std::string GetRefStructName();
private:
    std::string _RefStructName;
};
#endif // RECORD18_SNAME_H
