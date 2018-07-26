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
#include "inc/GDSIIModel/GDSIIDesign/GDSIIDesign.h"
#include "inc/GDSIIModel/GDSIIRecords/GDSIIRecord.h"
#include "inc/DataReader/RecordSupplier.h"
#include "inc/GDSIIModel/GDSIIStructure/Structure.h"
#include "inc/GDSIIModel/GDSIIElements/Boundary.h"
#include "inc/GDSIIModel/GDSIIElements/Path.h"
#include "inc/GDSIIModel/GDSIIElements/Node.h"

class GDSIIDesignReader {

public:
    GDSIIDesignReader();
    ~GDSIIDesignReader();
    std::shared_ptr<GDSIIDesign> MakeModel();    
private:

    std::set<short> layerMap;
    std::shared_ptr<GDSIIRecord> currentRecord;
    std::shared_ptr<GDSIIDesign> curDesign;

    std::shared_ptr<GDSIIStructure> curStructure;
    std::shared_ptr<GDSIIElement> curElement;


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

