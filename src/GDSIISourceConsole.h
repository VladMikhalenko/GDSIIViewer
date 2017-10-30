#ifndef GDSIISOURCECONSOLE_H
#define GDSIISOURCECONSOLE_H

#include "IGDSIISource.h"

using namespace std;
class GDSIISourceConsole : public IGDSIISource
{
    private:
        static GDSIISourceConsole* instance;
        GDSIISourceConsole();
        GDSIISourceConsole(const GDSIISourceConsole& orig);
        GDSIISourceConsole& operator=(GDSIISourceConsole const&);
    public:
       unsigned char* GetBytes(int byteCount);
       static GDSIISourceConsole* GetInstance();
};

#endif /* GDSIISOURCECONSOLE_H */
