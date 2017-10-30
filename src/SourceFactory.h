#ifndef SOURCEFACTORY_H
#define SOURCEFACTORY_H

#include "IGDSIISource.h"
#include "GDSIISourceConsole.h"
#include "GDSIISourceTXT.h"
#include "GlobalOptions.h"
#include "GDSIIBinSource.h"


class SourceFactory
{

public:
    static IGDSIISource* GetSource();
};

#endif // SOURCEFACTORY_H
