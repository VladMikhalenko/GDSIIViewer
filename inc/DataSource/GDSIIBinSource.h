#ifndef GDSIIBINSOURCE_H
#define GDSIIBINSOURCE_H
#include "inc/DataSource/IGDSIISource.h"
#include <fstream>

class GDSIIBinSource:public IGDSIISource
{
    GDSIIBinSource();
    GDSIIBinSource(const GDSIIBinSource& orig);
    GDSIIBinSource& operator=(GDSIIBinSource const&);
    std::fstream FileStream;
public:
    unsigned char *GetBytes(int byteCount);
    static GDSIIBinSource* GetInstance();
    void OpenFile();
};

#endif // GDSIIBINSOURCE_H
