/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GDSIIDesign.cpp
 * Author: Val
 *
 * Created on 2 января 2017 г., 18:39
 */

#include "GDSIIDesign.h"
#include <typeinfo>
#include <QTransform>
#include <QMessageBox>
GDSIIDesign::GDSIIDesign() {
}
GDSIIDesign::~GDSIIDesign()
{
}

GDSIIDesign::GDSIIDesign(const GDSIIDesign& orig) {
}

void GDSIIDesign::AddStructure(Structure *structure)
{
    structures.push_back(*structure);
}

LayerForView* GDSIIDesign::GetLayerForView(int layer){
    LayerForView* layForView=new LayerForView();
    for(int i=0;i<(int)structures.size();i++)
    {
        Structure str=structures[i];
        Point start_p;
        start_p.x_coord=0;
        start_p.y_coord=0;

        ScanStructureForLayer(&str, start_p,layer,0.0,1.0,layForView);
    }
    return layForView;
}
void GDSIIDesign::GetLayerForView(int layer, LayerForView* &layerForView)
{
    for(int i=0;i<(int)structures.size();i++)
    {
        Structure str=structures[i];
        Point start_p;
        start_p.x_coord=0;
        start_p.y_coord=0;

        ScanStructureForLayer(&str, start_p,layer,0.0,1.0,layerForView);
    }
}
LayerForView* GDSIIDesign::GetSeveralLayersForView(int amount_of_layers)
{
    LayerForView* lay=new LayerForView();
    for(int i=0;i<=amount_of_layers;i++)
    {
        GetLayerForView(i,lay);
    }
    return lay;
}

void  GDSIIDesign::ScanStructureForLayer(Structure *str, Point refPoint, int layer, double angle, double mag_coef, LayerForView *&layForView)
{
    for(int i=0;i<str->GetElementsCount();i++)
    {
        Element* curEl=str->GetElementByIndex(i);
        //QMessageBox::information(0,"Error","I am in ScanStruct Before 1 if has error:");
        if(curEl->GetLayer()==layer && curEl->GetID()!=EL_SREF && curEl->GetID()!=EL_AREF)
            RecountCoordsForElement(curEl,refPoint,angle,mag_coef,layForView);
        else if(curEl->GetID()==EL_SREF)
        {
            SREF* sref=dynamic_cast<SREF *>(curEl);
            Structure * str=GetStructureByName(sref->GetSNAME());
            if(str!=0)
            {
                Point refP=sref->GetPoints()[0];
                ScanStructureForLayer(str,refP,layer,sref->GetAngle(),sref->GetMAG(),layForView);
            }
        }
        else if(curEl->GetID()==EL_AREF)
        {
            AREF* aref=dynamic_cast<AREF *>(curEl);
            Structure * str=GetStructureByName(aref->GetSNAME());
            if(str!=0)
            {
                int col=aref->GetCOL();
                int row=aref->GetROW();

                Point refP=aref->GetPoints()[0];
                Point leftBottom=aref->GetPoints()[1];
                Point rightTop=aref->GetPoints()[2];

                int arrayWidth=leftBottom.x_coord-refP.x_coord;
                int arrayHeight=rightTop.y_coord-refP.y_coord;

                int cellWidth=arrayWidth/col;
                int cellHeight=arrayHeight/row;

                for(int i=refP.x_coord;i<arrayWidth;i+=cellWidth)//col*cellWidth;i+=cellWidth)
                {
                    for(int j=refP.y_coord;j<arrayHeight;j+=cellHeight)//row*cellHeight;j+=cellHeight)
                    {
                        Point newRef;
                        newRef.x_coord=i;//refP.x_coord+i;
                        newRef.y_coord=j;//refP.y_coord+j;
                        ScanStructureForLayer(str,newRef,layer,aref->GetAngle(),aref->GetMAG(),layForView);
                    }
                }
            }
        }
    }
}

void GDSIIDesign::RecountCoordsForElement(Element *el, Point refPoint, double angle, double mag_coef, LayerForView *&layerForView)
{
    //приведение типов проблема
    Element* copy=0;
    if(el->GetID()==EL_BOUNDARY)
    {
        Boundary* b=dynamic_cast<Boundary*>(el);
        copy=new Boundary();
        dynamic_cast<Boundary*>(copy)->SetDataType(b->GetDataType());
        dynamic_cast<Boundary*>(copy)->SetElFlags(b->GetElFlags());
        dynamic_cast<Boundary*>(copy)->SetPlex(b->GetPlex());
        dynamic_cast<Boundary*>(copy)->SetLayer(b->GetLayer());
        dynamic_cast<Boundary*>(copy)->SetPoints(b->GetPoints(),b->GetAmountOfPoints());
    }
    else if(el->GetID()==EL_PATH)
    {
        Path* p=dynamic_cast<Path*>(el);
        copy=new Path();
        dynamic_cast<Path*>(copy)->SetDataType(p->GetDataType());
        dynamic_cast<Path*>(copy)->SetElFlags(p->GetElFlags());
        dynamic_cast<Path*>(copy)->SetPlex(p->GetPlex());
        dynamic_cast<Path*>(copy)->SetLayer(p->GetLayer());
        dynamic_cast<Path*>(copy)->SetPoints(p->GetPoints(),p->GetAmountOfPoints());
    }

    Point* newPoints=new Point[el->GetAmountOfPoints()];
    double radAngle=angle*M_PI/180;
    for(int i=0;i<copy->GetAmountOfPoints();i++)
    {
        Point point_i=copy->GetPoints()[i];

        QTransform moveToRef(1,0,refPoint.x_coord,0,1,refPoint.y_coord,0,0,1);
        QTransform rotMat(cos(radAngle),-sin(radAngle),0,sin(radAngle),cos(radAngle),0,0,0,1);
        QTransform magMat(mag_coef,0,0,0,mag_coef,0,0,0,1);
        QTransform pointMat(point_i.x_coord,0,0,point_i.y_coord,0,0,1,0,0);
        QTransform newCoordsMat=moveToRef*rotMat*magMat*pointMat;
        int x_val=newCoordsMat.m11()>0?newCoordsMat.m11()+0.5:newCoordsMat.m11()-0.5;
        int y_val=newCoordsMat.m21()>0?newCoordsMat.m21()+0.5:newCoordsMat.m21()-0.5;
        newPoints[i].x_coord=x_val;
        newPoints[i].y_coord=y_val;
    }
    copy->SetPoints(newPoints,copy->GetAmountOfPoints());
    if(copy->GetID()==EL_BOUNDARY)
        layerForView->AddBoundary(dynamic_cast<Boundary*>(copy));
    else if(el->GetID()==EL_PATH)
        layerForView->AddPath(dynamic_cast<Path*>(copy));
    delete newPoints;
    delete copy;
}

void GDSIIDesign::SetUnitsData(double userSize, double metersSize){
    sizeInUserUnits=userSize;
    sizeInMeters=metersSize;
}

double GDSIIDesign::GetSizeInUserUnits(){
    return sizeInUserUnits;
}
double GDSIIDesign::GetSizeInMeters(){
    return sizeInMeters;
}

Structure* GDSIIDesign::GetStructureByName(std::__cxx11::string sname)
{
    Structure* strs=structures.data();
    for(int i=0;i<structures.size();i++)
    {
        Structure* curStr=&strs[i];
        if(curStr->GetStructureName()==sname)
        {
            return curStr;
        }
    }
    return 0;
}

void GDSIIDesign::ShowInfo()
{
    std::cout<<"Structures size"<<structures.size()<<"\n";
    for(int i=0;i<structures.size();i++)
    {
        Structure str=structures[i];
        std::cout<<"STR["<<i<<"]"<<str.GetStructureName()<<" has "<<str.GetElementsCount()<<" elems\n";
        //Element* elems=str.GetElementByIndex(i);
    }
}

int GDSIIDesign::GetNumOfStructures()
{
    return structures.size();
}
