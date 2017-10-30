/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GDSIIRecord.h
 * Author: Val
 *
 * Created on 2 января 2017 г., 14:49
 */

#ifndef GDSIIRECORD_H
#define GDSIIRECORD_H
enum RecordsID{
    HEADER=0,BGNLIB,LIBNAME,UNITS,ENDLIB,BGNSTR,STRNAME,ENDSTR,BOUNDARY,PATH,//0-9
    SREF_ID,AREF_ID,TEXT,LAYER,DATATYPE,WIDTH,XY,ENDEL,SNAME,COLROW,//10-19
    TEXTNODE,NODE,TEXTTYPE,PRESENTATION,/*SPACING=24,*/STRING=25,STRANS,MAG,ANGLE,/*UNINTEGER=29*/ //20-29
    /*USTRING=30*/REFLIBS=31,FONTS,PATHTYPE,GENERATIONS,ATTRTABLE,/*STYPTABLE=36*//*STRTYPE=37*/ELFLAGS=38,/*ELKEY=39*/ //30-39
    /*LINKTYPE=40*//*LINKKEYS=41*/NODETYPE=42,PROPATTR,PROPVALUE,BOX,BOXTYPE,PLEX,BGNEXTN,ENDEXTN,//40-49
    TAPENUM,TAPECODE,STRCLASS,/*RESERVED=53*/FORMAT=54,MASK,ENDMASKS,LIBDIRSIZE,SRFNAME,LIBSECUR//50-59
};

#include "SourceFactory.h"
#include "BinDataTypeReader.h"
#include <iostream>
#include <string>

class GDSIIRecord {
public:
    GDSIIRecord();
    GDSIIRecord(const GDSIIRecord& orig);
    virtual ~GDSIIRecord();
    int GetRecordID();
    virtual void Show();
protected:
    int recordID;
};

#endif /* GDSIIRECORD_H */

