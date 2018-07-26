#ifndef SOURCEFACTORY_H
#define SOURCEFACTORY_H

#include "IGDSIISource.h"
#include "GDSIISourceConsole.h"
#include "GDSIISourceTXT.h"
#include "inc/Global/GlobalOptions.h"
#include "GDSIIBinSource.h"

#include <memory>
class SourceFactory
{

public:
    static IGDSIISource* GetSource();
};

#endif // SOURCEFACTORY_H
