/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Record00_Header.cpp
 * Author: Val
 * 
 * Created on 2 января 2017 г., 14:53
 */

#include "inc/GDSIIModel/GDSIIRecords/Record00_Header.h"

Record00_Header::Record00_Header() {
    IGDSIISource* source=SourceFactory::GetSource();
    _VersionNumber = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID=HEADER;
}
Record00_Header::~Record00_Header() {
}

void Record00_Header::Show() {
    std::cout<<"<Record00_Header..."<<std::endl;
    std::cout<<"Version number: "<<_VersionNumber<<std::endl;
    std::cout<<"...Record00_Header>"<<std::endl;
}

short Record00_Header::GetVersionNumber() {
    return _VersionNumber;
}
