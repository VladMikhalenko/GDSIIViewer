#include "SourceFactory.h"
#include <cstring>

/*SourceFactory::SourceFactory(){

}
SourceFactory::~SourceFactory(){

}*/

IGDSIISource* SourceFactory::GetSource(){
    switch(GlobalOptions::GetSourceType()){
        case FILE_SOURCE:return GDSIIBinSource::GetInstance();
            break;
        case CONSOLE_SOURCE:return GDSIISourceConsole::GetInstance();
            break;
        case TEXT_SOURCE:return GDSIISourceTXT::GetInstance();
            break;
        case UNDEFINED:printf("Source type is not set");//throw AnError();
            break;
        default:return 0;//throw AnError();
            break;
    }
}
