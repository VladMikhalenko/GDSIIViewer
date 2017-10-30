#ifndef GDSIIBINSOURCE_H
#define GDSIIBINSOURCE_H
#include "src/IGDSIISource.h"
#include <fstream>

class GDSIIBinSource:public IGDSIISource
{
    static GDSIIBinSource* instance;
    GDSIIBinSource();
    GDSIIBinSource(const GDSIIBinSource& orig);
    GDSIIBinSource& operator=(GDSIIBinSource const&);
    std::fstream FileStream;
public:
    unsigned char* GetBytes(int byteCount);
    static GDSIIBinSource* GetInstance();
    void OpenFile();
};

#endif // GDSIIBINSOURCE_H
