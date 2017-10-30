/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GDSIIDesignReader.h
 * Author: Val
 *
 * Created on 2 января 2017 г., 18:40
 */

#ifndef GDSIIDESIGNREADER_H
#define GDSIIDESIGNREADER_H
#include "GDSIIDesign.h"
#include "GDSIIRecord.h"
#include "RecordSupplier.h"
#include "Structure.h"
#include "Boundary.h"
#include "Path.h"
#include "Node.h"

class GDSIIDesignReader {

public:
    GDSIIDesignReader();
    GDSIIDesignReader(const GDSIIDesignReader& orig);
    ~GDSIIDesignReader();
    GDSIIDesign* MakeModel();
private:
    GDSIIRecord* currentRecord;
    RecordSupplier* recSupplier;

    GDSIIDesign *curDesign;

    Structure *curStructure;
    Element *curElement;


    bool BNFStreamFormat();
    bool BNFFormatType();
    bool BNFStructure();
    bool BNFElement();
    bool BNFBoundary();
    bool BNFPath();
    bool BNFSREF();
    bool BNFAREF();
    bool BNFText();
    bool BNFNode();
    bool BNFBox();
    bool BNFTextBody();
    bool BNFStrans();
    bool BNFProperty();


    //header, bgnlib and the rest

    void UseBGNSTR();
    void UseSTRNAME();
    void UseSTRCLASS();
    void UseENDSTR();
    void UseUNITS();

    //Element
    void UseELFLAGS();
    void UsePLEX();
    void UseLAYER();
    void UseXY();
    void UseENDEL();

    //Boundary
    void UseBOUNDARY();
    void UseDATATYPE_Boundary();

    //Path
    void UsePATH();
    void UseDATATYPE_Path();
    void UsePATHTYPE_Path();
    void UseWIDTH_Path();
    void UseBGNEXTN();
    void UseENDEXTN();
    // SREF & AREF
    void UseSREF();
    void UseAREF();
    void UseSTRANS();
    void UseMAG();
    void UseANGLE();
    void UseSNAME();
    void UseCOLROW();





};

#endif /* GDSIIDESIGNREADER_H */

