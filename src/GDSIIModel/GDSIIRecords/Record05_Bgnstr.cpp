#include "inc/GDSIIModel/GDSIIRecords/Record05_Bgnstr.h"

Record05_Bgnstr::Record05_Bgnstr() {
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
    recordID=BGNSTR;
}

Record05_Bgnstr::~Record05_Bgnstr() {
}

void Record05_Bgnstr::Show() {
    std::cout << "Record05_Bgnstr..." << std::endl;
    std::cout << GetYearOfLastModification() << std::endl;
    std::cout << GetMonthOfLastModification() << std::endl;
    std::cout << GetDayOfLastModification() << std::endl;
    std::cout << GetHourOfLastModification() << std::endl;
    std::cout << GetMinuteOfLastModification() << std::endl;
    std::cout << GetSecondOfLastModification() << std::endl;

    std::cout << GetYearOfLastAccess() << std::endl;
    std::cout << GetMonthOfLastAccess() << std::endl;
    std::cout << GetDayOfLastAccess() << std::endl;
    std::cout << GetHourOfLastAccess() << std::endl;
    std::cout << GetMinuteOfLastAccess() << std::endl;
    std::cout << GetSecondOfLastAccess() << std::endl;
    std::cout << "...Record05_Bgnstr" << std::endl;
}

short Record05_Bgnstr::GetYearOfLastModification() {
    return _yearOfLastModification;
}

short Record05_Bgnstr::GetMonthOfLastModification() {
    return _monthOfLastModification;
}

short Record05_Bgnstr::GetDayOfLastModification() {
    return _dayOfLastModification;
}

short Record05_Bgnstr::GetHourOfLastModification() {
    return _hourOfLastModification;
}

short Record05_Bgnstr::GetMinuteOfLastModification() {
    return _minuteOfLastModification;
}

short Record05_Bgnstr::GetSecondOfLastModification() {
    return _secondOfLastModification;
}

short Record05_Bgnstr::GetYearOfLastAccess() {
    return _yearOfLastAccess;
}

short Record05_Bgnstr::GetMonthOfLastAccess() {
    return _monthOfLastAccess;
}

short Record05_Bgnstr::GetDayOfLastAccess() {
    return _dayOfLastAccess;
}

short Record05_Bgnstr::GetHourOfLastAccess() {
    return _hourOfLastAccess;
}

short Record05_Bgnstr::GetMinuteOfLastAccess() {
    return _minuteOfLastAccess;
}

short Record05_Bgnstr::GetSecondOfLastAccess() {
    return _secondOfLastAccess;
}
