/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GDSIIDesignReader.cpp
 * Author: Val
 * 
 * Created on 2 января 2017 г., 18:40
 */

#include "inc/DataReader/GDSIIDesignReader.h"
#include "inc/Global/AnError.h"
#include <typeinfo>
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

#include <QMessageBox>

//#define DYNAMIC_SHARED_CAST (Type) (std::dynamic_pointer_cast<Type,GDSIIRecord>(currentRecord))
GDSIIDesignReader::GDSIIDesignReader():
    currentRecord(nullptr),
    curDesign(nullptr),
    curStructure(nullptr),
    curElement(nullptr)
{
}

GDSIIDesignReader::~GDSIIDesignReader() {
}

std::shared_ptr<GDSIIDesign> GDSIIDesignReader::MakeModel()
{
    curDesign=std::make_shared<GDSIIDesign>(GDSIIDesign());
    currentRecord=RecordSupplier::GetInstance().NextRecord();
    if(BNFStreamFormat())
        return curDesign;
    else
    {
        curDesign.reset();
    }//throw AnError();
    return curDesign;
}

bool GDSIIDesignReader::BNFStreamFormat(){

    //Общее для всех методов BNF
        //1.Возвращают true / false
        //false - если в потоке данных - нарушения правил
        //true
        //2.Перед выходом считывают следующую запись

    //HEADER
    if (currentRecord->GetRecordID()== HEADER){
        //UseHeader(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    else return false;
    //BGNLIB
    if(currentRecord->GetRecordID()==BGNLIB){
        //UseBGNLib(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    else return false;

    //[LIBDIRSIZE]
    if (currentRecord->GetRecordID()== LIBDIRSIZE)
    {
        //UseLIBDIRSIZE(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    if (currentRecord->GetRecordID()== SRFNAME)
    {
        //UseSRFNAME(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    if (currentRecord->GetRecordID()== LIBSECUR)
    {
        //UseLIBSECUR(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    if (currentRecord->GetRecordID()== LIBNAME)
    {
        //UseLIBNAME(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    else return false;

    //[REFLIBS]
    if (currentRecord->GetRecordID()== REFLIBS)
    {
        //UseREFLIBS(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    if (currentRecord->GetRecordID()== FONTS)
    {
        //UseFONTS(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    if (currentRecord->GetRecordID()== ATTRTABLE){
        //UseATTRTABLE(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    if (currentRecord->GetRecordID()== GENERATIONS){
        //UseGENERATIONS(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    if (!BNFFormatType())
        return false;
    if (currentRecord->GetRecordID()== UNITS){
        UseUNITS();
        currentRecord=RecordSupplier::GetInstance().NextRecord();
    }
    else return false;
    //structures
    while (currentRecord->GetRecordID()== BGNSTR){
        if (!BNFStructure()) return false;
    }

    if (currentRecord->GetRecordID()==ENDLIB){
        //UseENDLIB(currentRecord);
        //currentRecord=RecordSupplier::GetInstance().NextRecord();
        return true;
    }
    else throw AnError();
}
//not actual right now
bool GDSIIDesignReader::BNFFormatType(){
    if (currentRecord->GetRecordID()== FORMAT)
        {
            //UseFORMAT(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
            bool hasMask=false;
            while (currentRecord->GetRecordID()== MASK)
            {
                hasMask=true;
                //UseMask(currentRecord);
                currentRecord=RecordSupplier::GetInstance().NextRecord();
            }
            if (hasMask)
            {
                if(currentRecord->GetRecordID()== ENDMASKS)
                {
                    //UseENDMASK(currentRecord);
                    currentRecord=RecordSupplier::GetInstance().NextRecord();
                    return true;
                }
                else return false;
            }
        }
    return true;

}

bool GDSIIDesignReader::BNFStructure(){
    if(currentRecord->GetRecordID()==BGNSTR){
        UseBGNSTR();
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==STRNAME){
            UseSTRNAME();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==STRCLASS){
            UseSTRCLASS();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        //else return false;

        while(currentRecord->GetRecordID()==BOUNDARY ||
              currentRecord->GetRecordID()==PATH ||
              currentRecord->GetRecordID()==SREF_ID ||
              currentRecord->GetRecordID()==AREF_ID ||
              currentRecord->GetRecordID()==TEXT ||
              currentRecord->GetRecordID()==NODE ||
              currentRecord->GetRecordID()==BOX)
        {
            if(!BNFElement()) return false;
        }

        if(currentRecord->GetRecordID()==ENDSTR){
            UseENDSTR();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
            return true;
        }
        else return false;

        return true;
    }
    else return false;

}

bool GDSIIDesignReader::BNFElement(){
    if(currentRecord->GetRecordID()==BOUNDARY){
        if(!BNFBoundary()) return false;
    }
    else if(currentRecord->GetRecordID()==PATH){
        if(!BNFPath()) return false;
    }
    else if(currentRecord->GetRecordID()==SREF_ID){
        if(!BNFSREF()) return false;
    }
    else if(currentRecord->GetRecordID()==AREF_ID){
        if(!BNFAREF()) return false;
    }
    else if(currentRecord->GetRecordID()==TEXT){
        if(!BNFText()) return false;
    }
    else if(currentRecord->GetRecordID()==NODE){
        if(!BNFNode()) return false;
    }
    else if(currentRecord->GetRecordID()==BOX){
        if(!BNFBox()) return false;
    }
    else return false;

    while(currentRecord->GetRecordID()==PROPATTR){
        if(!BNFProperty())return false;
    }

    if(currentRecord->GetRecordID()==ENDEL){
        UseENDEL();

        currentRecord=RecordSupplier::GetInstance().NextRecord();
        return true;
    }
    else return false;

    return true;

}

bool GDSIIDesignReader::BNFBoundary(){
    if(currentRecord->GetRecordID()==BOUNDARY){
        UseBOUNDARY();
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            UseELFLAGS();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            UsePLEX();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            UseLAYER();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==DATATYPE){
            UseDATATYPE_Boundary();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==XY){
            UseXY();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        return true;
    }
    else return false;

}

bool GDSIIDesignReader::BNFPath(){
    if(currentRecord->GetRecordID()==PATH){
        UsePATH();
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            UseELFLAGS();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            UsePLEX();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            UseLAYER();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==DATATYPE){
            UseDATATYPE_Path();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==PATHTYPE){
            UsePATHTYPE_Path();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==WIDTH){
            UseWIDTH_Path();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==BGNEXTN){
            UseBGNEXTN();
            currentRecord=RecordSupplier::GetInstance().NextRecord();

            if(currentRecord->GetRecordID()==ENDEXTN){
                UseENDEXTN();
                currentRecord=RecordSupplier::GetInstance().NextRecord();
            }
            else return false;
        }
        if(currentRecord->GetRecordID()==XY){
            UseXY();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        return true;
    }
    else return false;
}
//прогнать отладку чтения угла и коефа масштабирования
bool GDSIIDesignReader::BNFSREF(){
    if(currentRecord->GetRecordID()==SREF_ID){
        UseSREF();
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            UseELFLAGS();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            UseELFLAGS();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==SNAME){
            UseSNAME();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==STRANS){
            if(!BNFStrans()) return false;
        }
        if(currentRecord->GetRecordID()==XY){
            UseXY();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        return true;
    }
    else return false;
}

bool GDSIIDesignReader::BNFAREF(){
    if(currentRecord->GetRecordID()==AREF_ID){
        UseAREF();
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            UseELFLAGS();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            UsePLEX();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==SNAME){
            UseSNAME();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==STRANS){
            if(!BNFStrans()) return false;
        }
        if(currentRecord->GetRecordID()==COLROW){
            UseCOLROW();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==XY){
            UseXY();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        return true;
    }
    else return false;
}

bool GDSIIDesignReader::BNFText(){
    if(currentRecord->GetRecordID()==TEXT){
        //UseTEXT(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            //UseELFLAGS(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            //UseELFLAGS(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            //UseLAYER(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==TEXTTYPE){
            if(!BNFTextBody()) return false;
        }

        return true;
    }
    return false;
}

bool GDSIIDesignReader::BNFNode(){
    if(currentRecord->GetRecordID()==NODE){
        //UseNODE(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            //UseELFLAGS(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            //UseELFLAGS(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            //UseLAYER(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==NODETYPE){
            //UseNODETYPE(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==XY){
            //UseXY(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        return true;
    }
}

bool GDSIIDesignReader::BNFBox(){
    if(currentRecord->GetRecordID()==BOX){
        //UseBOX(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            //UseELFLAGS(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            //UseELFLAGS(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            //UseLAYER(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==BOXTYPE){
            //UseBOXTYPE(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==XY){
            //UseXY(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;
        return true;
    }

}

bool GDSIIDesignReader::BNFTextBody(){
    if(currentRecord->GetRecordID()==TEXTTYPE){
        //UseTEXTTYPE(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==PRESENTATION){
            //UsePRESENTATION(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==PATHTYPE){
            //UsePATHTYPE(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==WIDTH){
            //UseWIDTH(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }

        if(currentRecord->GetRecordID()==STRANS){
            if(!BNFStrans()) return false;
        }
        if(currentRecord->GetRecordID()==XY){
            //UseXY(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==STRING){
            //UseSTRING(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;

        return true;
    }
    return false;
}

bool GDSIIDesignReader::BNFStrans(){
    if(currentRecord->GetRecordID()==STRANS){
        UseSTRANS();
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==MAG){
            UseMAG();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        if(currentRecord->GetRecordID()==ANGLE){
            UseANGLE();
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
    }
    return true;

}

bool GDSIIDesignReader::BNFProperty(){
    if(currentRecord->GetRecordID()==PROPATTR){
        //UsePROPATTR(currentRecord);
        currentRecord=RecordSupplier::GetInstance().NextRecord();

        if(currentRecord->GetRecordID()==PROPVALUE){
            //UseVALUE(currentRecord);
            currentRecord=RecordSupplier::GetInstance().NextRecord();
        }
        else return false;
        return true;
    }
    return false;
}


void GDSIIDesignReader::UseBGNSTR()
{
    curStructure=std::make_shared<GDSIIStructure>(GDSIIStructure());
}
void GDSIIDesignReader::UseSTRNAME()
{
    curStructure->SetStructureName(std::dynamic_pointer_cast<Record06_Strname,GDSIIRecord>(currentRecord)->GetStructureName());
}
void GDSIIDesignReader::UseSTRCLASS()
{
    curStructure->SetStrClass(std::dynamic_pointer_cast<Record52_Strclass,GDSIIRecord>(currentRecord)->GetInfo());
}
void GDSIIDesignReader::UseENDSTR()
{
    curDesign->AddStructure(*curStructure);
    //delete curStructure;
    curStructure.reset();
}
void GDSIIDesignReader::UseUNITS()
{
    std::shared_ptr<Record03_Units> unit_record= std::dynamic_pointer_cast<Record03_Units,GDSIIRecord>(currentRecord);
    curDesign->SetUnitsData(unit_record->GetSizeInUserUnits(),unit_record->GetSizeInMeters());
}

void GDSIIDesignReader::UseBOUNDARY()
{
    curElement=std::make_shared<Boundary>(Boundary());
}
void GDSIIDesignReader::UseELFLAGS()
{
    curElement->SetElFlags(std::dynamic_pointer_cast<Record38_Elflags,GDSIIRecord>(currentRecord)->GetElflags());
}
void GDSIIDesignReader::UsePLEX()
{
    curElement->SetPlex(std::dynamic_pointer_cast<Record47_Plex,GDSIIRecord>(currentRecord)->GetPlex());
}
void GDSIIDesignReader::UseLAYER()
{
    short layerValue = std::dynamic_pointer_cast<Record13_Layer,GDSIIRecord>(currentRecord)->GetLayer();
    curDesign->SaveLayer(layerValue);
    curElement->SetLayer(layerValue);
}
void GDSIIDesignReader::UseDATATYPE_Boundary()
{
    std::dynamic_pointer_cast<Boundary,GDSIIElement>(curElement)->SetDataType(std::dynamic_pointer_cast<Record14_Datatype,GDSIIRecord>(currentRecord)->GetDatatype());
}
void GDSIIDesignReader::UseXY()
{
    std::shared_ptr<Record16_XY> rec_16=std::dynamic_pointer_cast<Record16_XY,GDSIIRecord>(currentRecord);
    std::vector<GDSIIPoint> pts=rec_16->GetPoints();
    curElement->SetPoints(pts,rec_16->GetPointsAmount());
}
void GDSIIDesignReader::UseENDEL(){
    curStructure->AddElement(curElement);
    curElement.reset();
}

void GDSIIDesignReader::UsePATH()
{
    curElement=std::make_shared<Path>(Path());
}
void GDSIIDesignReader::UsePATHTYPE_Path()
{
    std::dynamic_pointer_cast<Path,GDSIIElement>(curElement)->SetPathType(std::dynamic_pointer_cast<Record33_Pathtype,GDSIIRecord>(currentRecord)->GetPathtype());
}
void GDSIIDesignReader::UseDATATYPE_Path()
{
    std::dynamic_pointer_cast<Path,GDSIIElement>(curElement)->SetDataType(std::dynamic_pointer_cast<Record14_Datatype,GDSIIRecord>(currentRecord)->GetDatatype());
}
void GDSIIDesignReader::UseWIDTH_Path()
{
    std::dynamic_pointer_cast<Path,GDSIIElement>(curElement)->SetWidth(std::dynamic_pointer_cast<Record15_Width,GDSIIRecord>(currentRecord)->GetWidth());
}
void GDSIIDesignReader::UseBGNEXTN()
{
    std::dynamic_pointer_cast<Path,GDSIIElement>(curElement)->SetBgnExtn(std::dynamic_pointer_cast<Record48_Bgnextn,GDSIIRecord>(currentRecord)->GetExtension());
}
void GDSIIDesignReader::UseENDEXTN(){
    std::dynamic_pointer_cast<Path,GDSIIElement>(curElement)->SetEndExtn(std::dynamic_pointer_cast<Record49_Endextn,GDSIIRecord>(currentRecord)->GetExtension());
}

void GDSIIDesignReader::UseSREF()
{
    curElement=std::make_shared<SREF>(SREF());
}
void GDSIIDesignReader::UseAREF()
{
    curElement=std::make_shared<AREF>(AREF());
}

void GDSIIDesignReader::UseSTRANS()
{
    //SREF_ID* sref=reinterpret_cast<SREF_ID*>(curElement);
    //????
}
void GDSIIDesignReader::UseANGLE()
{
    if(curElement->GetID()==EL_SREF)
    {
        std::shared_ptr<SREF> sref=std::dynamic_pointer_cast<SREF,GDSIIElement>(curElement);
        sref->SetAngle(std::dynamic_pointer_cast<Record28_Angle,GDSIIRecord>(currentRecord)->GetRotation());
    }
    else if(curElement->GetID()==EL_AREF)
    {
        std::shared_ptr<AREF> aref=std::dynamic_pointer_cast<AREF,GDSIIElement>(curElement);
        aref->SetAngle(std::dynamic_pointer_cast<Record28_Angle,GDSIIRecord>(currentRecord)->GetRotation());
    }

}
void GDSIIDesignReader::UseMAG()
{
    std::shared_ptr<SREF> sref=std::dynamic_pointer_cast<SREF,GDSIIElement>(curElement);
    sref->SetMAG(std::dynamic_pointer_cast<Record27_Mag,GDSIIRecord>(currentRecord)->GetMagnificationFactor());
}
void GDSIIDesignReader::UseSNAME()
{
    if(curElement->GetID()==EL_SREF)
    {
        std::shared_ptr<SREF> sref=std::dynamic_pointer_cast<SREF,GDSIIElement>(curElement);
        sref->SetSNAME(std::dynamic_pointer_cast<Record18_Sname,GDSIIRecord>(currentRecord)->GetRefStructName());
    }
    else if(curElement->GetID()==EL_AREF)
    {
        std::shared_ptr<AREF> aref=std::dynamic_pointer_cast<AREF,GDSIIElement>(curElement);
        aref->SetSNAME(std::dynamic_pointer_cast<Record18_Sname,GDSIIRecord>(currentRecord)->GetRefStructName());
    }
}
void GDSIIDesignReader::UseCOLROW()
{
    std::shared_ptr<AREF> aref=std::dynamic_pointer_cast<AREF,GDSIIElement>(curElement);
    aref->SetCOL(std::dynamic_pointer_cast<Record19_Colrow,GDSIIRecord>(currentRecord)->GetColnum());
    aref->SetROW(std::dynamic_pointer_cast<Record19_Colrow,GDSIIRecord>(currentRecord)->GetRownum());
}
