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

#include "GDSIIDesignReader.h"
#include "AnError.h"
#include <typeinfo>
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


#include <QMessageBox>
GDSIIDesignReader::GDSIIDesignReader() {
    recSupplier=RecordSupplier::GetInstance();
    currentRecord=0;
}

GDSIIDesignReader::GDSIIDesignReader(const GDSIIDesignReader& orig) {
}

GDSIIDesignReader::~GDSIIDesignReader() {
    delete currentRecord;

    //delete curDesign;
    //delete curStructure;
    //delete curElement;
}

GDSIIDesign* GDSIIDesignReader::MakeModel()
{
    curDesign=new GDSIIDesign();
    currentRecord=recSupplier->NextRecord();
    if(BNFStreamFormat())
        return curDesign;
    else
    {
        delete curDesign;
        curDesign=0;
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
        currentRecord=recSupplier->NextRecord();
    }
    else return false;
    //BGNLIB
    if(currentRecord->GetRecordID()==BGNLIB){
        //UseBGNLib(currentRecord);
        currentRecord=recSupplier->NextRecord();
    }
    else return false;

    //[LIBDIRSIZE]
    if (currentRecord->GetRecordID()== LIBDIRSIZE)
    {
        //UseLIBDIRSIZE(currentRecord);
        currentRecord=recSupplier->NextRecord();
    }
    if (currentRecord->GetRecordID()== SRFNAME)
    {
        //UseSRFNAME(currentRecord);
        currentRecord=recSupplier->NextRecord();
    }
    if (currentRecord->GetRecordID()== LIBSECUR)
    {
        //UseLIBSECUR(currentRecord);
        currentRecord=recSupplier->NextRecord();
    }
    if (currentRecord->GetRecordID()== LIBNAME)
    {
        //UseLIBNAME(currentRecord);
        currentRecord=recSupplier->NextRecord();
    }
    else return false;

    //[REFLIBS]
    if (currentRecord->GetRecordID()== REFLIBS)
    {
        //UseREFLIBS(currentRecord);
        currentRecord=recSupplier->NextRecord();
    }
    if (currentRecord->GetRecordID()== FONTS)
    {
        //UseFONTS(currentRecord);
        currentRecord=recSupplier->NextRecord();
    }
    if (currentRecord->GetRecordID()== ATTRTABLE){
        //UseATTRTABLE(currentRecord);
        currentRecord=recSupplier->NextRecord();
    }
    if (currentRecord->GetRecordID()== GENERATIONS){
        //UseGENERATIONS(currentRecord);
        currentRecord=recSupplier->NextRecord();
    }
    if (!BNFFormatType())
        return false;
    if (currentRecord->GetRecordID()== UNITS){
        UseUNITS();
        currentRecord=recSupplier->NextRecord();
    }
    else return false;
    //structures
    while (currentRecord->GetRecordID()== BGNSTR){
        if (!BNFStructure()) return false;
    }

    if (currentRecord->GetRecordID()==ENDLIB){
        //UseENDLIB(currentRecord);
        //currentRecord=recSupplier->NextRecord();
        return true;
    }
    else throw AnError();
}
//not actual right now
bool GDSIIDesignReader::BNFFormatType(){
    if (currentRecord->GetRecordID()== FORMAT)
        {
            //UseFORMAT(currentRecord);
            currentRecord=recSupplier->NextRecord();
            bool hasMask=false;
            while (currentRecord->GetRecordID()== MASK)
            {
                hasMask=true;
                //UseMask(currentRecord);
                currentRecord=recSupplier->NextRecord();
            }
            if (hasMask)
            {
                if(currentRecord->GetRecordID()== ENDMASKS)
                {
                    //UseENDMASK(currentRecord);
                    currentRecord=recSupplier->NextRecord();
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
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==STRNAME){
            UseSTRNAME();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==STRCLASS){
            UseSTRCLASS();
            currentRecord=recSupplier->NextRecord();
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
            currentRecord=recSupplier->NextRecord();
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

        currentRecord=recSupplier->NextRecord();
        return true;
    }
    else return false;

    return true;

}

bool GDSIIDesignReader::BNFBoundary(){
    if(currentRecord->GetRecordID()==BOUNDARY){
        UseBOUNDARY();
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            UseELFLAGS();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            UsePLEX();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            UseLAYER();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==DATATYPE){
            UseDATATYPE_Boundary();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==XY){
            UseXY();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        return true;
    }
    else return false;

}

bool GDSIIDesignReader::BNFPath(){
    if(currentRecord->GetRecordID()==PATH){
        UsePATH();
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            UseELFLAGS();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            UsePLEX();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            UseLAYER();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==DATATYPE){
            UseDATATYPE_Path();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==PATHTYPE){
            UsePATHTYPE_Path();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==WIDTH){
            UseWIDTH_Path();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==BGNEXTN){
            UseBGNEXTN();
            currentRecord=recSupplier->NextRecord();

            if(currentRecord->GetRecordID()==ENDEXTN){
                UseENDEXTN();
                currentRecord=recSupplier->NextRecord();
            }
            else return false;
        }
        if(currentRecord->GetRecordID()==XY){
            UseXY();
            currentRecord=recSupplier->NextRecord();
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
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            UseELFLAGS();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            UseELFLAGS();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==SNAME){
            UseSNAME();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==STRANS){
            if(!BNFStrans()) return false;
        }
        if(currentRecord->GetRecordID()==XY){
            UseXY();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        return true;
    }
    else return false;
}

bool GDSIIDesignReader::BNFAREF(){
    if(currentRecord->GetRecordID()==AREF_ID){
        UseAREF();
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            UseELFLAGS();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            UsePLEX();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==SNAME){
            UseSNAME();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==STRANS){
            if(!BNFStrans()) return false;
        }
        if(currentRecord->GetRecordID()==COLROW){
            UseCOLROW();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==XY){
            UseXY();
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        return true;
    }
    else return false;
}

bool GDSIIDesignReader::BNFText(){
    if(currentRecord->GetRecordID()==TEXT){
        //UseTEXT(currentRecord);
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            //UseELFLAGS(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            //UseELFLAGS(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            //UseLAYER(currentRecord);
            currentRecord=recSupplier->NextRecord();
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
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            //UseELFLAGS(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            //UseELFLAGS(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            //UseLAYER(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==NODETYPE){
            //UseNODETYPE(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==XY){
            //UseXY(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        return true;
    }
}

bool GDSIIDesignReader::BNFBox(){
    if(currentRecord->GetRecordID()==BOX){
        //UseBOX(currentRecord);
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==ELFLAGS){
            //UseELFLAGS(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==PLEX){
            //UseELFLAGS(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==LAYER){
            //UseLAYER(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==BOXTYPE){
            //UseBOXTYPE(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==XY){
            //UseXY(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        return true;
    }
}

bool GDSIIDesignReader::BNFTextBody(){
    if(currentRecord->GetRecordID()==TEXTTYPE){
        //UseTEXTTYPE(currentRecord);
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==PRESENTATION){
            //UsePRESENTATION(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==PATHTYPE){
            //UsePATHTYPE(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==WIDTH){
            //UseWIDTH(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }

        if(currentRecord->GetRecordID()==STRANS){
            if(!BNFStrans()) return false;
        }
        if(currentRecord->GetRecordID()==XY){
            //UseXY(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        if(currentRecord->GetRecordID()==STRING){
            //UseSTRING(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        else return false;

        return true;
    }
    return false;
}

bool GDSIIDesignReader::BNFStrans(){
    if(currentRecord->GetRecordID()==STRANS){
        UseSTRANS();
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==MAG){
            UseMAG();
            currentRecord=recSupplier->NextRecord();
        }
        if(currentRecord->GetRecordID()==ANGLE){
            UseANGLE();
            currentRecord=recSupplier->NextRecord();
        }
    }
    return true;

}

bool GDSIIDesignReader::BNFProperty(){
    if(currentRecord->GetRecordID()==PROPATTR){
        //UsePROPATTR(currentRecord);
        currentRecord=recSupplier->NextRecord();

        if(currentRecord->GetRecordID()==PROPVALUE){
            //UseVALUE(currentRecord);
            currentRecord=recSupplier->NextRecord();
        }
        else return false;
        return true;
    }
    return false;
}


void GDSIIDesignReader::UseBGNSTR()
{
    curStructure=new Structure();
}
void GDSIIDesignReader::UseSTRNAME()
{
    curStructure->SetStructureName(reinterpret_cast<Record06_Strname*>(currentRecord)->GetStructureName());
}
void GDSIIDesignReader::UseSTRCLASS()
{
    curStructure->SetStrClass(reinterpret_cast<Record52_Strclass*>(currentRecord)->GetInfo());
}
void GDSIIDesignReader::UseENDSTR()
{
    curDesign->AddStructure(curStructure);
    delete curStructure;
    curStructure=0;
}
void GDSIIDesignReader::UseUNITS()
{
    Record03_Units* unit_record= reinterpret_cast<Record03_Units*>(currentRecord);
    curDesign->SetUnitsData(unit_record->GetSizeInUserUnits(),unit_record->GetSizeInMeters());
}

void GDSIIDesignReader::UseBOUNDARY()
{
    curElement=new Boundary();
}
void GDSIIDesignReader::UseELFLAGS()
{
    curElement->SetElFlags(reinterpret_cast<Record38_Elflags*>(currentRecord)->GetElflags());
}
void GDSIIDesignReader::UsePLEX()
{
    curElement->SetPlex(reinterpret_cast<Record47_Plex*>(currentRecord)->GetPlex());
}
void GDSIIDesignReader::UseLAYER()
{
   curElement->SetLayer(reinterpret_cast<Record13_Layer*>(currentRecord)->GetLayer());
}
void GDSIIDesignReader::UseDATATYPE_Boundary()
{
    reinterpret_cast<Boundary*>(curElement)->SetDataType(reinterpret_cast<Record14_Datatype*>(currentRecord)->GetDatatype());
}
void GDSIIDesignReader::UseXY()
{
    Record16_XY* rec_16=reinterpret_cast<Record16_XY*>(currentRecord);
    Point* pts=rec_16->GetPoints();
    /*for(int i=0;i<rec_16->GetPointsAmount();i++)
    {
        pts[i].x_coord*=curDesign->GetSizeInUserUnits();//как считать????
        pts[i].y_coord*=curDesign->GetSizeInUserUnits();//
    }*/
    curElement->SetPoints(pts,rec_16->GetPointsAmount());
}
void GDSIIDesignReader::UseENDEL(){
    curStructure->AddElement(curElement);
    //delete curElement;
    curElement=0;
}

void GDSIIDesignReader::UsePATH()
{
    curElement=new Path();
}
void GDSIIDesignReader::UsePATHTYPE_Path()
{
    reinterpret_cast<Path*>(curElement)->SetPathType(reinterpret_cast<Record33_Pathtype*>(currentRecord)->GetPathtype());
}
void GDSIIDesignReader::UseDATATYPE_Path()
{
    reinterpret_cast<Path*>(curElement)->SetDataType(reinterpret_cast<Record14_Datatype*>(currentRecord)->GetDatatype());
}
void GDSIIDesignReader::UseWIDTH_Path()
{
    reinterpret_cast<Path*>(curElement)->SetWidth(reinterpret_cast<Record15_Width*>(currentRecord)->GetWidth());
}
void GDSIIDesignReader::UseBGNEXTN()
{
    reinterpret_cast<Path*>(curElement)->SetBgnExtn(reinterpret_cast<Record48_Bgnextn*>(currentRecord)->GetExtension());
}
void GDSIIDesignReader::UseENDEXTN(){
    reinterpret_cast<Path*>(curElement)->SetEndExtn(reinterpret_cast<Record49_Endextn*>(currentRecord)->GetExtension());
}

void GDSIIDesignReader::UseSREF()
{
    curElement=new SREF();
}
void GDSIIDesignReader::UseAREF()
{
    curElement=new AREF();
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
        SREF* sref=reinterpret_cast<SREF*>(curElement);
        sref->SetAngle(reinterpret_cast<Record28_Angle*>(currentRecord)->GetRotation());
    }
    else if(curElement->GetID()==EL_AREF)
    {
        AREF* aref=reinterpret_cast<AREF*>(curElement);
        aref->SetAngle(reinterpret_cast<Record28_Angle*>(currentRecord)->GetRotation());
    }

}
void GDSIIDesignReader::UseMAG()
{
    SREF* sref=reinterpret_cast<SREF*>(curElement);
    sref->SetMAG(reinterpret_cast<Record27_Mag*>(currentRecord)->GetMagnificationFactor());
}
void GDSIIDesignReader::UseSNAME()
{
    if(curElement->GetID()==EL_SREF)
    {
        SREF* sref=reinterpret_cast<SREF*>(curElement);
        sref->SetSNAME(reinterpret_cast<Record18_Sname*>(currentRecord)->GetRefStructName());
    }
    else if(curElement->GetID()==EL_AREF)
    {
        AREF* aref=reinterpret_cast<AREF*>(curElement);
        aref->SetSNAME(reinterpret_cast<Record18_Sname*>(currentRecord)->GetRefStructName());
    }
}
void GDSIIDesignReader::UseCOLROW()
{
    AREF* aref=reinterpret_cast<AREF*>(curElement);
    aref->SetCOL(reinterpret_cast<Record19_Colrow*>(currentRecord)->GetColnum());
    aref->SetROW(reinterpret_cast<Record19_Colrow*>(currentRecord)->GetRownum());
}
