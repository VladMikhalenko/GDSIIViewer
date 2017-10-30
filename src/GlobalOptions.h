#ifndef GLOBALOPTIONS_H
#define GLOBALOPTIONS_H
#include <string>

enum SourceType{UNDEFINED=-1,CONSOLE_SOURCE=0,TEXT_SOURCE=1,FILE_SOURCE=2};

class GlobalOptions
{
    static SourceType sourceType;
    static std::string fileName;
public:
    GlobalOptions();
    static SourceType GetSourceType();
    static std::string GetFileName();
    static void SetSourceType(SourceType type);
    static void SetFileName(std::string name);
};

#endif // GLOBALOPTIONS_H
