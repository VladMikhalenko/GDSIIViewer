/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Record00_Header.h
 * Author: Val
 *
 * Created on 2 января 2017 г., 14:53
 */

#ifndef RECORD00_HEADER_H
#define RECORD00_HEADER_H
#include "GDSIIRecord.h"

class Record00_Header:public GDSIIRecord
{
public:
    Record00_Header();
    Record00_Header(const Record00_Header& orig);
    virtual ~Record00_Header();
    void Show();
    short GetVersionNumber();
private:
    short _VersionNumber;

};

#endif /* RECORD00_HEADER_H */

