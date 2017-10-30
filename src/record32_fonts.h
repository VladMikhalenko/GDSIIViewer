#ifndef RECORD32_FONTS_H
#define RECORD32_FONTS_H
#include "GDSIIRecord.h"
#include <string>

class Record32_Fonts:public GDSIIRecord
{
public:
    Record32_Fonts(int str_size);
    Record32_Fonts(const Record32_Fonts& orig);
    virtual ~Record32_Fonts();

    void Show();
    std::string GetFirstName();
    std::string GetSecondName();
    std::string GetThirdName();
    std::string GetFourthName();
private:
    std::string _FontNames;
};
#endif // RECORD32_FONTS_H
