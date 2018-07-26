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

#include "inc/GDSIIModel/GDSIIDesign/GDSIIDesign.h"
#include "inc/GDSIIModel/GDSIIElements/AREF.h"
#include "inc/GDSIIModel/GDSIIElements/SREF.h"
#include "inc/GDSIIModel/GDSIIElements/Boundary.h"
#include "inc/GDSIIModel/GDSIIElements/Path.h"

#include "utils/Convert/GDSIIConverter.h"

#include <memory>
#include <typeinfo>
#include <QTransform>
#include <QMessageBox>
GDSIIDesign::GDSIIDesign():
    VersionNumber(0),
    LibName(),
    sizeInUserUnits(0),
    sizeInMeters(0),
    _layerSet()
{
}
GDSIIDesign::~GDSIIDesign()
{
}


std::set<short> GDSIIDesign::GetLayersSet() const
{
    return _layerSet;
}
void GDSIIDesign::SaveLayer(const short &layer)
{
    _layerSet.insert(layer);
}

void GDSIIDesign::AddStructure(const GDSIIStructure &structure)
{
    structures.push_back(structure);
}

std::shared_ptr<LayerForView> GDSIIDesign::GetLayerForView(int layer){
    std::shared_ptr<LayerForView> layForView=std::make_shared<LayerForView>(LayerForView());
    for(auto it=structures.begin();it!=structures.end();it++)//GDSIIStructure str:structures)//int i=0;i<(int)structures.size();i++)
    {
        //GDSIIStructure str=structures[i];
        //GDSIIPoint start_p(0,0);
        ScanStructureForLayer(*it, GDSIIPoint(0,0),layer,0.0,1.0,layForView);
    }
    return layForView;
}
void GDSIIDesign::GetLayerForView(int layer, std::shared_ptr<LayerForView> &layerForView)
{
    for(unsigned i=0;i<structures.size();i++)
    {
        GDSIIStructure str=structures[i];
        GDSIIPoint start_p(0,0);

        ScanStructureForLayer(str, start_p,layer,0.0,1.0,layerForView);
    }
}
std::shared_ptr<LayerForView> GDSIIDesign::GetFullDesignLayerForView()
{
    std::shared_ptr<LayerForView> lay=std::make_shared<LayerForView>(LayerForView());
    for(auto it = _layerSet.begin();it!=_layerSet.end();it++)
    {
        GetLayerForView(*it,lay);
    }
//    for(int i=0;i<=amount_of_layers;i++)
//    {
//        GetLayerForView(i,lay);
//    }
    return lay;
}

void  GDSIIDesign::ScanStructureForLayer(const GDSIIStructure &str, const GDSIIPoint &refPoint, int layer, double angle, double mag_coef, std::shared_ptr<LayerForView> &layForView)
{
    for(int i=0;i<str.GetElementsCount();i++)
    {
        std::shared_ptr<GDSIIElement> curEl=str.GetElementByIndex(i);
        //QMessageBox::information(0,"Error","I am in ScanStruct Before 1 if has error:");
        if(curEl->GetLayer()==layer && curEl->GetID()!=EL_SREF && curEl->GetID()!=EL_AREF)
            RecountCoordsForElement(curEl,refPoint,angle,mag_coef,layForView);
        else if(curEl->GetID()==EL_SREF)
        {
            std::shared_ptr<SREF> sref=std::dynamic_pointer_cast<SREF,GDSIIElement>(curEl);
            std::shared_ptr<GDSIIStructure> nstr=GetStructureByName(sref->GetSNAME());
            if(nstr.get()!=nullptr)
            {
                GDSIIPoint refP=sref->GetPoints()[0];
                ScanStructureForLayer(*nstr,refP,layer,sref->GetAngle(),sref->GetMAG(),layForView);
            }
        }
        else if(curEl->GetID()==EL_AREF)
        {
            std::shared_ptr<AREF> aref=std::dynamic_pointer_cast<AREF,GDSIIElement>(curEl);
            std::shared_ptr<GDSIIStructure> nstr=GetStructureByName(aref->GetSNAME());
            if(nstr.get()!=nullptr)
            {
                int col=aref->GetCOL();
                int row=aref->GetROW();

                GDSIIPoint refP=aref->GetPoints()[0];
                GDSIIPoint leftBottom=aref->GetPoints()[1];
                GDSIIPoint rightTop=aref->GetPoints()[2];

                int arrayWidth=leftBottom.GetX()-refP.GetX();
                int arrayHeight=rightTop.GetY()-refP.GetY();

                int cellWidth=arrayWidth/col;
                int cellHeight=arrayHeight/row;

                for(int i=refP.GetX();i<arrayWidth;i+=cellWidth)//col*cellWidth;i+=cellWidth)
                {
                    for(int j=refP.GetY();j<arrayHeight;j+=cellHeight)//row*cellHeight;j+=cellHeight)
                    {
                        GDSIIPoint newRef(i,j);
                        //refP.x_coord+i;
                        //refP.y_coord+j;
                        ScanStructureForLayer(*nstr,newRef,layer,aref->GetAngle(),aref->GetMAG(),layForView);
                    }
                }
            }
        }
    }
}

void GDSIIDesign::RecountCoordsForElement(const std::shared_ptr<GDSIIElement> &el, const GDSIIPoint &refPoint, double angle, double mag_coef, std::shared_ptr<LayerForView> &layerForView)
{    
    std::shared_ptr<GDSIIElement> copy=GDSIIConverter::GetInstance().CopyElement(el);//std::const_pointer_cast<GDSIIElement,GDSIIElement>(el); //std::make_shared<GDSIIElement>(el);
//    if(el->GetID()==EL_BOUNDARY)
//    {
//        Boundary* b=dynamic_cast<Boundary*>(el);
//        copy=new Boundary();
//        dynamic_cast<Boundary*>(copy)->SetDataType(b->GetDataType());
//        dynamic_cast<Boundary*>(copy)->SetElFlags(b->GetElFlags());
//        dynamic_cast<Boundary*>(copy)->SetPlex(b->GetPlex());
//        dynamic_cast<Boundary*>(copy)->SetLayer(b->GetLayer());
//        dynamic_cast<Boundary*>(copy)->SetPoints(b->GetPoints(),b->GetAmountOfPoints());
//    }
//    else if(el->GetID()==EL_PATH)
//    {
//        Path* p=dynamic_cast<Path*>(el);
//        copy=new Path();
//        dynamic_cast<Path*>(copy)->SetDataType(p->GetDataType());
//        dynamic_cast<Path*>(copy)->SetElFlags(p->GetElFlags());
//        dynamic_cast<Path*>(copy)->SetPlex(p->GetPlex());
//        dynamic_cast<Path*>(copy)->SetLayer(p->GetLayer());
//        dynamic_cast<Path*>(copy)->SetPoints(p->GetPoints(),p->GetAmountOfPoints());
//    }
    //??????THINK
    std::vector<GDSIIPoint> newPoints(el->GetAmountOfPoints());//new GDSIIPoint[el->GetAmountOfPoints()];
    double radAngle=angle*M_PI/180;
    for(int i=0;i<copy->GetAmountOfPoints();i++)
    {
        GDSIIPoint point_i=copy->GetPoints()[i];

        QTransform moveToRef(1,0,refPoint.GetX(),0,1,refPoint.GetY(),0,0,1);
        QTransform rotMat(cos(radAngle),-sin(radAngle),0,sin(radAngle),cos(radAngle),0,0,0,1);
        QTransform magMat(mag_coef,0,0,0,mag_coef,0,0,0,1);
        QTransform pointMat(point_i.GetX(),0,0,point_i.GetY(),0,0,1,0,0);
        QTransform newCoordsMat=moveToRef*rotMat*magMat*pointMat;
        int x_val=newCoordsMat.m11()>0?newCoordsMat.m11()+0.5:newCoordsMat.m11()-0.5;
        int y_val=newCoordsMat.m21()>0?newCoordsMat.m21()+0.5:newCoordsMat.m21()-0.5;
        newPoints[i].SetX(x_val);
        newPoints[i].SetY(y_val);
    }
    copy->SetPoints(newPoints,copy->GetAmountOfPoints());
    if(copy->GetID()==EL_BOUNDARY)
        layerForView->AddBoundary(std::dynamic_pointer_cast<Boundary,GDSIIElement>(copy).get());
    else if(el->GetID()==EL_PATH)
        layerForView->AddPath(std::dynamic_pointer_cast<Path,GDSIIElement>(copy).get());
    //delete newPoints;
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

std::shared_ptr<GDSIIStructure> GDSIIDesign::GetStructureByName(const std::__cxx11::string &sname)
{
    for(auto it=structures.begin();it!=structures.end();it++)//unsigned i=0;i<structures.size();i++)
    {
        //std::shared_ptr<GDSIIStructure> curStr=std::make_shared<GDSIIStructure>(structures[i]);
        if(it->GetStructureName()==sname)
            return std::make_shared<GDSIIStructure>(*it);
    }
    return std::shared_ptr<GDSIIStructure>(nullptr);
}

void GDSIIDesign::ShowInfo()
{
    std::cout<<"Structures size"<<structures.size()<<"\n";
    for(unsigned i=0;i<structures.size();i++)
    {
        GDSIIStructure str=structures[i];
        std::cout<<"STR["<<i<<"]"<<str.GetStructureName()<<" has "<<str.GetElementsCount()<<" elems\n";
        //Element* elems=str.GetElementByIndex(i);
    }
}
int GDSIIDesign::GetNumOfStructures()
{
    return structures.size();
}
