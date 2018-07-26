#ifndef GDSIISOURCECONSOLE_H
#define GDSIISOURCECONSOLE_H

#include "IGDSIISource.h"

class GDSIISourceConsole : public IGDSIISource
{
    private:
        GDSIISourceConsole();
        GDSIISourceConsole(const GDSIISourceConsole& orig);
        GDSIISourceConsole& operator=(GDSIISourceConsole const&);
    public:
       unsigned char* GetBytes(int byteCount);
       static GDSIISourceConsole* GetInstance();
};

#endif /* GDSIISOURCECONSOLE_H */
