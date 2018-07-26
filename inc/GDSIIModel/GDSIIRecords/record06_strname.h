#ifndef RECORD06_STRNAME_H
#define RECORD06_STRNAME_H
#include "GDSIIRecord.h"
#include <string>

class Record06_Strname:public GDSIIRecord
{
public:
    Record06_Strname(int str_size);
    virtual ~Record06_Strname();

    void Show();
    std::string GetStructureName();
private:
    std::string _StructureName;
};
#endif // RECORD06_STRNAME_H
