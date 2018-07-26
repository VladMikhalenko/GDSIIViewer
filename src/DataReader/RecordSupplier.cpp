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

#include "inc/DataReader/RecordSupplier.h"
#include "inc/DataSource/SourceFactory.h"
#include "inc/Global/AnError.h"
#include "inc/GDSIIModel/GDSIIRecords/Record00_Header.h"
#include "inc/GDSIIModel/GDSIIRecords/record01_bgnlib.h"
#include "inc/GDSIIModel/GDSIIRecords/record02_libname.h"
#include "inc/GDSIIModel/GDSIIRecords/Record03_Units.h"
#include "inc/GDSIIModel/GDSIIRecords/record04_endlib.h"
#include "inc/GDSIIModel/GDSIIRecords/Record05_Bgnstr.h"
#include "inc/GDSIIModel/GDSIIRecords/record06_strname.h"
#include "inc/GDSIIModel/GDSIIRecords/Record07_Endstr.h"
#include "inc/GDSIIModel/GDSIIRecords/record08_boundary.h"
#include "inc/GDSIIModel/GDSIIRecords/Record09_Path.h"
#include "inc/GDSIIModel/GDSIIRecords/record10_sref.h"
#include "inc/GDSIIModel/GDSIIRecords/Record11_Aref.h"
#include "inc/GDSIIModel/GDSIIRecords/record12_text.h"
#include "inc/GDSIIModel/GDSIIRecords/Record13_Layer.h"
#include "inc/GDSIIModel/GDSIIRecords/record14_datatype.h"
#include "inc/GDSIIModel/GDSIIRecords/Record15_Width.h"
#include "inc/GDSIIModel/GDSIIRecords/Record16_XY.h"
#include "inc/GDSIIModel/GDSIIRecords/Record17_Endel.h"
#include "inc/GDSIIModel/GDSIIRecords/record18_sname.h"
#include "inc/GDSIIModel/GDSIIRecords/Record19_Colrow.h"
#include "inc/GDSIIModel/GDSIIRecords/record20_textnode.h"
#include "inc/GDSIIModel/GDSIIRecords/Record21_Node.h"
#include "inc/GDSIIModel/GDSIIRecords/record22_texttype.h"
#include "inc/GDSIIModel/GDSIIRecords/Record23_Presentation.h"
#include "inc/GDSIIModel/GDSIIRecords/record24_spacing.h"
#include "inc/GDSIIModel/GDSIIRecords/Record25_String.h"
#include "inc/GDSIIModel/GDSIIRecords/record26_strans.h"
#include "inc/GDSIIModel/GDSIIRecords/Record27_Mag.h"
#include "inc/GDSIIModel/GDSIIRecords/record28_angle.h"
#include "inc/GDSIIModel/GDSIIRecords/Record31_Reflibs.h"
#include "inc/GDSIIModel/GDSIIRecords/record32_fonts.h"
#include "inc/GDSIIModel/GDSIIRecords/Record33_Pathtype.h"
#include "inc/GDSIIModel/GDSIIRecords/record34_generations.h"
#include "inc/GDSIIModel/GDSIIRecords/Record35_Attrtable.h"
#include "inc/GDSIIModel/GDSIIRecords/record36_styptable.h"
#include "inc/GDSIIModel/GDSIIRecords/Record37_Strtype.h"
#include "inc/GDSIIModel/GDSIIRecords/record38_elflags.h"
#include "inc/GDSIIModel/GDSIIRecords/Record39_Elkey.h"
#include "inc/GDSIIModel/GDSIIRecords/record40_linktype.h"
#include "inc/GDSIIModel/GDSIIRecords/Record41_Linkeys.h"
#include "inc/GDSIIModel/GDSIIRecords/record42_nodetype.h"
#include "inc/GDSIIModel/GDSIIRecords/Record43_Propattr.h"
#include "inc/GDSIIModel/GDSIIRecords/record44_propvalue.h"
#include "inc/GDSIIModel/GDSIIRecords/Record45_Box.h"
#include "inc/GDSIIModel/GDSIIRecords/record46_boxtype.h"
#include "inc/GDSIIModel/GDSIIRecords/Record47_Plex.h"
#include "inc/GDSIIModel/GDSIIRecords/record48_bgnextn.h"
#include "inc/GDSIIModel/GDSIIRecords/Record49_Endextn.h"
#include "inc/GDSIIModel/GDSIIRecords/record50_tapenum.h"
#include "inc/GDSIIModel/GDSIIRecords/Record51_Tapecode.h"
#include "inc/GDSIIModel/GDSIIRecords/record52_strclass.h"
#include "inc/GDSIIModel/GDSIIRecords/Record53_Reserved.h"
#include "inc/GDSIIModel/GDSIIRecords/record54_format.h"
#include "inc/GDSIIModel/GDSIIRecords/Record55_Mask.h"
#include "inc/GDSIIModel/GDSIIRecords/record56_endmasks.h"
#include "inc/GDSIIModel/GDSIIRecords/Record57_Libdirsize.h"
#include "inc/GDSIIModel/GDSIIRecords/record58_srfname.h"
#include "inc/GDSIIModel/GDSIIRecords/Record59_Libsecur.h"

RecordSupplier::RecordSupplier() {
    source=SourceFactory::GetSource();
}
RecordSupplier &RecordSupplier::GetInstance(){
    static RecordSupplier _instance;
    return _instance;
}

std::shared_ptr<GDSIIRecord> RecordSupplier::NextRecord()
{
    unsigned short recordLength=0;
    unsigned short bytesLeft=0;
    short recType;
    //short dataType;
    short rec_and_data=0;

    recordLength=static_cast<unsigned short>(BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2));

    //record type and data type
    rec_and_data=BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    bytesLeft=recordLength-4;

    recType=rec_and_data>>8;//rec_and_data >> 8 positions right
    //dataType=rec_and_data&255;//rec_and_data & 0000 0000 1111 1111

    //printf("Record header: total length: [%04#x](%-2d bytes); RecordType|DataType : [%02x|%02x]; Data part: %d\n",recordLength,recordLength,recType,dataType,recordLength-4);
    //printf("I've got info about record!!\n");
    switch(recType){
        case HEADER:  return std::shared_ptr<Record00_Header>(new Record00_Header());//ok
            break;
        case BGNLIB:  return std::shared_ptr<Record01_Bgnlib>(new Record01_Bgnlib());//ok
            break;
        case LIBNAME: return std::shared_ptr<Record02_Libname>(new Record02_Libname(bytesLeft));//ok
            break;
        case UNITS:   return std::shared_ptr<Record03_Units>(new Record03_Units());//ok
            break;
        case ENDLIB:  return std::shared_ptr<Record04_Endlib>(new Record04_Endlib());//ok
            break;
        case BGNSTR:  return std::shared_ptr<Record05_Bgnstr>(new Record05_Bgnstr());//ok
            break;
        case STRNAME: return std::shared_ptr<Record06_Strname>(new Record06_Strname(bytesLeft));//ok
            break;
        case ENDSTR:  return std::shared_ptr<Record07_Endstr>(new Record07_Endstr());//ok
            break;
        case BOUNDARY:return std::shared_ptr<Record08_Boundary>(new Record08_Boundary());//ok
            break;
        case PATH:    return std::shared_ptr<Record09_Path>(new Record09_Path());//ok
            break;
        case SREF_ID: return std::shared_ptr<Record10_Sref>(new Record10_Sref());//ok
            break;
        case AREF_ID: return std::shared_ptr<Record11_Aref>(new Record11_Aref());//ok
            break;
        case TEXT:    return std::shared_ptr<Record12_Text>(new Record12_Text());//ok
            break;
        case LAYER:   return std::shared_ptr<Record13_Layer>(new Record13_Layer());//ok
            break;
        case DATATYPE:return std::shared_ptr<Record14_Datatype>(new Record14_Datatype());//ok
            break;
        case WIDTH:   return std::shared_ptr<Record15_Width>(new Record15_Width());//ok
            break;
        case XY:      return std::shared_ptr<Record16_XY>(new Record16_XY(bytesLeft/8));// ok bytesLeft/4 ->num of values and /2 ->num of points
            break;
        case ENDEL:   return std::shared_ptr<Record17_Endel>(new Record17_Endel());//ok
            break;
        case SNAME:   return std::shared_ptr<Record18_Sname>(new Record18_Sname(bytesLeft));//ok
            break;
        case COLROW:  return std::shared_ptr<Record19_Colrow>(new Record19_Colrow());//ok
            break;
        case TEXTNODE:return std::shared_ptr<Record20_Textnode>(new Record20_Textnode());//ok
            break;
        case NODE:    return std::shared_ptr<Record21_Node>(new Record21_Node());//ok
            break;
        case TEXTTYPE:return std::shared_ptr<Record22_Texttype>(new Record22_Texttype());//ok
            break;
        case PRESENTATION:return std::shared_ptr<Record23_Presentation>(new Record23_Presentation());//ok
            break;
        //case SPACING:
        //    break;
        case STRING:  return std::shared_ptr<Record25_String>(new Record25_String(bytesLeft));//ok
            break;
        case STRANS:  return std::shared_ptr<Record26_Strans>(new Record26_Strans());//ok
            break;
        case MAG:     return std::shared_ptr<Record27_Mag>(new Record27_Mag());//ok
            break;
        case ANGLE:   return std::shared_ptr<Record28_Angle>(new Record28_Angle());//ok
            break;
        //case UNIINTEGER:
        //    break;
        //case USTRING:
        //    break;
        case REFLIBS:  return std::shared_ptr<Record31_Reflibs>(new Record31_Reflibs(bytesLeft));//ok
            break;
        case FONTS:    return std::shared_ptr<Record32_Fonts>(new Record32_Fonts(bytesLeft));//ok
            break;
        case PATHTYPE: return std::shared_ptr<Record33_Pathtype>(new Record33_Pathtype());
            break;
        case GENERATIONS:return std::shared_ptr<Record34_Generations>(new Record34_Generations());
            break;
        case ATTRTABLE: return std::shared_ptr<Record35_Attrtable>(new Record35_Attrtable(bytesLeft));
            break;
        //case STYPTABLE:
        //    break;
        //case STRTYPE:
        //    break;
        case ELFLAGS:return std::shared_ptr<Record38_Elflags>(new Record38_Elflags());
            break;
        //case ELKEY:
        //    break;
        //case LINKTYPE:
        //    break;
        //case LINKKEYS:
        //    break;
        case NODETYPE:  return std::shared_ptr<Record42_Nodetype>(new Record42_Nodetype());
            break;
        case PROPATTR:  return std::shared_ptr<Record43_Propattr>(new Record43_Propattr());
            break;
        case PROPVALUE: return std::shared_ptr<Record44_Propvalue>(new Record44_Propvalue(bytesLeft));
            break;
        case BOX:       return std::shared_ptr<Record45_Box>(new Record45_Box());
            break;
        case BOXTYPE:   return std::shared_ptr<Record46_Boxtype>(new Record46_Boxtype());
            break;
        case PLEX:      return std::shared_ptr<Record47_Plex>(new Record47_Plex());
            break;
        case BGNEXTN:   return std::shared_ptr<Record48_Bgnextn>(new Record48_Bgnextn());
            break;
        case ENDEXTN:   return std::shared_ptr<Record49_Endextn>(new Record49_Endextn());
            break;
        case TAPENUM:   return std::shared_ptr<Record50_Tapenum>(new Record50_Tapenum());
            break;
        case TAPECODE:  return std::shared_ptr<Record51_Tapecode>(new Record51_Tapecode());
            break;
        case STRCLASS:  return std::shared_ptr<Record52_Strclass>(new Record52_Strclass());
            break;
        //case RESERVED:
        //    break;
        case FORMAT:    return std::shared_ptr<Record54_Format>(new Record54_Format());
            break;
        case MASK:      return std::shared_ptr<Record55_Mask>(new Record55_Mask(bytesLeft));
            break;
        case ENDMASKS:  return std::shared_ptr<Record56_Endmasks>(new Record56_Endmasks());
            break;
        case LIBDIRSIZE:return std::shared_ptr<Record57_Libdirsize>(new Record57_Libdirsize());
            break;
        case SRFNAME:   return std::shared_ptr<Record58_Srfname>(new Record58_Srfname(bytesLeft));
            break;
        case LIBSECUR:  return std::shared_ptr<Record59_Libsecur>(new Record59_Libsecur(bytesLeft/6));
            break;
        default:        return std::shared_ptr<GDSIIRecord>(nullptr);
            break;
    }
}
