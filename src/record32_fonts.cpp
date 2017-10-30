#include "Record32_Fonts.h"

Record32_Fonts::Record32_Fonts(int str_size) {
    IGDSIISource* source=SourceFactory::GetSource();
    _FontNames = BinDataTypeReader::_ASCIIString(source->GetBytes(str_size),str_size);
    recordID = FONTS;
}

Record32_Fonts::Record32_Fonts(const Record32_Fonts& orig) {
}

Record32_Fonts::~Record32_Fonts() {
}

void Record32_Fonts::Show() {
    std::cout<<"<Record32_Fonts..."<<std::endl;
    std::cout<<"First name: "<<GetFirstName()<<std::endl;
    std::cout<<"Second name: "<<GetSecondName()<<std::endl;
    std::cout<<"Third name: "<<GetThirdName()<<std::endl;
    std::cout<<"Fourth name: "<<GetFourthName()<<std::endl;
    std::cout<<"...Record32_Fonts>"<<std::endl;
}

std::string Record32_Fonts::GetFirstName() {
    return _FontNames.substr(0, 44);
}

std::string Record32_Fonts::GetSecondName() {
    return _FontNames.substr(44, 44);
}

std::string Record32_Fonts::GetThirdName() {
    return _FontNames.substr(88, 44);
}

std::string Record32_Fonts::GetFourthName() {
    return _FontNames.substr(132, 44);
}
