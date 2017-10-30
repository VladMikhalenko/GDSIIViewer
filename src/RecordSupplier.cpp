/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinGDSIIFileReader.cpp
 * Author: Val
 * 
 * Created on 2 января 2017 г., 16:40
 */

#include "RecordSupplier.h"
#include "AnError.h"
#include "SourceFactory.h"
#include "Record00_Header.h"
#include "record01_bgnlib.h"
#include "record02_libname.h"
#include "Record03_Units.h"
#include "record04_endlib.h"
#include "Record05_Bgnstr.h"
#include "record06_strname.h"
#include "Record07_Endstr.h"
#include "record08_boundary.h"
#include "Record09_Path.h"
#include "record10_sref.h"
#include "Record11_Aref.h"
#include "record12_text.h"
#include "Record13_Layer.h"
#include "record14_datatype.h"
#include "Record15_Width.h"
#include "Record16_XY.h"
#include "Record17_Endel.h"
#include "record18_sname.h"
#include "Record19_Colrow.h"
#include "record20_textnode.h"
#include "Record21_Node.h"
#include "record22_texttype.h"
#include "Record23_Presentation.h"
#include "record24_spacing.h"
#include "Record25_String.h"
#include "record26_strans.h"
#include "Record27_Mag.h"
#include "record28_angle.h"
#include "Record31_Reflibs.h"
#include "record32_fonts.h"
#include "Record33_Pathtype.h"
#include "record34_generations.h"
#include "Record35_Attrtable.h"
#include "record36_styptable.h"
#include "Record37_Strtype.h"
#include "record38_elflags.h"
#include "Record39_Elkey.h"
#include "record40_linktype.h"
#include "Record41_Linkeys.h"
#include "record42_nodetype.h"
#include "Record43_Propattr.h"
#include "record44_propvalue.h"
#include "Record45_Box.h"
#include "record46_boxtype.h"
#include "Record47_Plex.h"
#include "record48_bgnextn.h"
#include "Record49_Endextn.h"
#include "record50_tapenum.h"
#include "Record51_Tapecode.h"
#include "record52_strclass.h"
#include "Record53_Reserved.h"
#include "record54_format.h"
#include "Record55_Mask.h"
#include "record56_endmasks.h"
#include "Record57_Libdirsize.h"
#include "record58_srfname.h"
#include "Record59_Libsecur.h"

RecordSupplier::RecordSupplier() {
    source=SourceFactory::GetSource();
}
RecordSupplier* RecordSupplier::GetInstance(){
    if(instance==0)
    {
        instance=new RecordSupplier();
    }
    return instance;
}

RecordSupplier::~RecordSupplier() {
    delete source;
}

GDSIIRecord* RecordSupplier::NextRecord()
{
    unsigned short recordLength=0;
    unsigned short bytesLeft=0;
    short recType;
    //short dataType;
    short rec_and_data=0;

    recordLength=(unsigned short)BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);

    //record type and data type
    rec_and_data=BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    bytesLeft=recordLength-4;

    recType=rec_and_data>>8;//rec_and_data >> 8 positions right
    //dataType=rec_and_data&255;//rec_and_data & 0000 0000 1111 1111

    //printf("Record header: total length: [%04#x](%-2d bytes); RecordType|DataType : [%02x|%02x]; Data part: %d\n",recordLength,recordLength,recType,dataType,recordLength-4);
    //printf("I've got info about record!!\n");
    switch(recType){
        case HEADER:return new Record00_Header();//ok
            break;
        case BGNLIB:return new Record01_Bgnlib();//ok
            break;
        case LIBNAME:return new Record02_Libname(bytesLeft);//ok
            break;
        case UNITS:return new Record03_Units();//ok
            break;
        case ENDLIB:return new Record04_Endlib();//ok
            break;
        case BGNSTR:return new Record05_Bgnstr();//ok
            break;
        case STRNAME:return new Record06_Strname(bytesLeft);//ok
            break;
        case ENDSTR:return new Record07_Endstr();//ok
            break;
        case BOUNDARY:return new Record08_Boundary();//ok
            break;
        case PATH:return new Record09_Path();//ok
            break;
        case SREF_ID:return new Record10_Sref();//ok
            break;
        case AREF_ID:return new Record11_Aref();//ok
            break;
        case TEXT:return new Record12_Text();//ok
            break;
        case LAYER:return new Record13_Layer();//ok
            break;
        case DATATYPE:return new Record14_Datatype();//ok
            break;
        case WIDTH:return new Record15_Width();//ok
            break;
        case XY:return new Record16_XY(bytesLeft/8);// ok bytesLeft/4 ->num of values and /2 ->num of points
            break;
        case ENDEL:return new Record17_Endel();//ok
            break;
        case SNAME:return new Record18_Sname(bytesLeft);//ok
            break;
        case COLROW:return new Record19_Colrow();//ok
            break;
        case TEXTNODE:return new Record20_Textnode();//ok
            break;
        case NODE:return new Record21_Node();//ok
            break;
        case TEXTTYPE:return new Record22_Texttype();//ok
            break;
        case PRESENTATION:return new Record23_Presentation();//ok
            break;
        //case SPACING:
        //    break;
        case STRING:return new Record25_String(bytesLeft);//ok
            break;
        case STRANS:return new Record26_Strans();//ok
            break;
        case MAG:return new Record27_Mag();//ok
            break;
        case ANGLE:return new Record28_Angle();//ok
            break;
        //case UNIINTEGER:
        //    break;
        //case USTRING:
        //    break;
        case REFLIBS:return new Record31_Reflibs(bytesLeft);//ok
            break;
        case FONTS:return new Record32_Fonts(bytesLeft);//ok
            break;
        case PATHTYPE:return new Record33_Pathtype();
            break;
        case GENERATIONS:return new Record34_Generations();
            break;
        case ATTRTABLE:return new Record35_Attrtable(bytesLeft);
            break;
        //case STYPTABLE:
        //    break;
        //case STRTYPE:
        //    break;
        case ELFLAGS:return new Record38_Elflags();
            break;
        //case ELKEY:
        //    break;
        //case LINKTYPE:
        //    break;
        //case LINKKEYS:
        //    break;
        case NODETYPE:return new Record42_Nodetype();
            break;
        case PROPATTR:return new Record43_Propattr();
            break;
        case PROPVALUE:return new Record44_Propvalue(bytesLeft);
            break;
        case BOX:return new Record45_Box();
            break;
        case BOXTYPE:return new Record46_Boxtype();
            break;
        case PLEX:return new Record47_Plex();
            break;
        case BGNEXTN:return new Record48_Bgnextn();
            break;
        case ENDEXTN:return new Record49_Endextn();
            break;
        case TAPENUM:return new Record50_Tapenum();
            break;
        case TAPECODE:return new Record51_Tapecode();
            break;
        case STRCLASS:return new Record52_Strclass();
            break;
        //case RESERVED:
        //    break;
        case FORMAT:return new Record54_Format();
            break;
        case MASK:return new Record55_Mask(bytesLeft);
            break;
        case ENDMASKS:return new Record56_Endmasks();
            break;
        case LIBDIRSIZE:return new Record57_Libdirsize();
            break;
        case SRFNAME:return new Record58_Srfname(bytesLeft);
            break;
        case LIBSECUR:return new Record59_Libsecur(bytesLeft/6);
            break;
        default:return 0;
            break;
    }
}

RecordSupplier* RecordSupplier::instance =0;
