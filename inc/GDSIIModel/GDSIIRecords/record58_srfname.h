#ifndef RECORD58_SRFNAME_H
#define RECORD58_SRFNAME_H
#include "GDSIIRecord.h"
#include <string>

class Record58_Srfname:public GDSIIRecord
{
public:
    Record58_Srfname(int str_size);
    Record58_Srfname(const Record58_Srfname& orig);
    virtual ~Record58_Srfname();

    void Show();
    std::string GetSRFName();
private:
    std::string _SRFName;
};
#endif // RECORD58_SRFNAME_H
