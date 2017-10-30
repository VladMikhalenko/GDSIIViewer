#ifndef RECORD06_STRNAME_H
#define RECORD06_STRNAME_H
#include "GDSIIRecord.h"
#include <string>

class Record06_Strname:public GDSIIRecord
{
public:
    Record06_Strname(int str_size);
    Record06_Strname(const Record06_Strname& orig);
    virtual ~Record06_Strname();

    void Show();
    std::string GetStructureName();
private:
    std::string _StructureName;
};
#endif // RECORD06_STRNAME_H
