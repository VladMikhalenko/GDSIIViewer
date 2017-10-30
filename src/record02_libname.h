#ifndef RECORD02_LIBNAME_H
#define RECORD02_LIBNAME_H
#include "GDSIIRecord.h"
#include <string>

class Record02_Libname:public GDSIIRecord
{
public:
    Record02_Libname(int str_size);
    Record02_Libname(const Record02_Libname& orig);
    virtual ~Record02_Libname();

    void Show();
    std::string GetLibraryName();
private:
    std::string _LibraryName;
};
#endif // RECORD02_LIBNAME_H
