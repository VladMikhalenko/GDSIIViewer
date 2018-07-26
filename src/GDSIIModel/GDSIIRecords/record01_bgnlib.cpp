#include "inc/GDSIIModel/GDSIIRecords/Record01_Bgnlib.h"

Record01_Bgnlib::Record01_Bgnlib() {
    IGDSIISource* source=SourceFactory::GetSource();
    _yearOfLastModification = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _monthOfLastModification = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _dayOfLastModification = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _hourOfLastModification = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _minuteOfLastModification = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _secondOfLastModification = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);

    _yearOfLastAccess = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _monthOfLastAccess = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _dayOfLastAccess = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _hourOfLastAccess = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _minuteOfLastAccess = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    _secondOfLastAccess = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID=BGNLIB;
}

Record01_Bgnlib::~Record01_Bgnlib() {
}

void Record01_Bgnlib::Show() {
     std::cout << "Record01_Bgnlib..." << std::endl;
     std::cout << GetYearOfLastModificaton() << std::endl;
     std::cout << GetMonthOfLastModificaton() << std::endl;
     std::cout << GetDayOfLastModificaton() << std::endl;
     std::cout << GetHourOfLastModificaton() << std::endl;
     std::cout << GetMinuteOfLastModificaton() << std::endl;
     std::cout << GetSecondOfLastModificaton() << std::endl;

     std::cout << GetYearOfLastAccess() << std::endl;
     std::cout << GetMonthOfLastAccess() << std::endl;
     std::cout << GetDayOfLastAccess() << std::endl;
     std::cout << GetHourOfLastAccess() << std::endl;
     std::cout << GetMinuteOfLastAccess() << std::endl;
     std::cout << GetSecondOfLastAccess() << std::endl;
     std::cout << "...Record1_Bgnlib" << std::endl;
}

short Record01_Bgnlib::GetYearOfLastModificaton() {
    return _yearOfLastModification;
}

short Record01_Bgnlib::GetMonthOfLastModificaton() {
    return _monthOfLastModification;
}
short Record01_Bgnlib::GetDayOfLastModificaton() {
    return _dayOfLastModification;
}

short Record01_Bgnlib::GetHourOfLastModificaton() {
    return _hourOfLastModification;
}

short Record01_Bgnlib::GetMinuteOfLastModificaton() {
    return _minuteOfLastModification;
}

short Record01_Bgnlib::GetSecondOfLastModificaton() {
    return _secondOfLastModification;
}

short Record01_Bgnlib::GetYearOfLastAccess() {
    return _yearOfLastAccess;
}

short Record01_Bgnlib::GetMonthOfLastAccess() {
    return _monthOfLastAccess;
}

short Record01_Bgnlib::GetDayOfLastAccess() {
    return _dayOfLastAccess;
}

short Record01_Bgnlib::GetHourOfLastAccess() {
    return _hourOfLastAccess;
}

short Record01_Bgnlib::GetMinuteOfLastAccess() {
    return _minuteOfLastAccess;
}

short Record01_Bgnlib::GetSecondOfLastAccess() {
    return _secondOfLastAccess;
}
