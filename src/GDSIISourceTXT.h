#ifndef GDSIISOURCETXT_H
#define GDSIISOURCETXT_H

#include "IGDSIISource.h"
#include <fstream>

class GDSIISourceTXT:public IGDSIISource
{
    static GDSIISourceTXT* instance;
    GDSIISourceTXT();
    GDSIISourceTXT(const GDSIISourceTXT& orig);
    GDSIISourceTXT& operator=(GDSIISourceTXT const&);
    std::fstream FileStream;
public:
    unsigned char* GetBytes(int byteCount);
    static GDSIISourceTXT* GetInstance();
    void OpenFile();
};

#endif // GDSIISOURCETXT_H
