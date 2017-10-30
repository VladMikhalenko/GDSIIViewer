/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GDSIIDesign.h
 * Author: Val
 *
 * Created on 2 января 2017 г., 18:39
 */

#ifndef GDSIIDESIGN_H
#define GDSIIDESIGN_H

#include "Structure.h"
#include <vector>
#include "LayerForView.h"
#include <QtCore>
class GDSIIDesign {
public:
    GDSIIDesign();
    GDSIIDesign(const GDSIIDesign& orig);
    ~GDSIIDesign();

    void AddStructure(Structure* structure);
    LayerForView* GetLayerForView(int layer);
    void GetLayerForView(int layer, LayerForView* &layerForView);
    LayerForView* GetSeveralLayersForView(int amount_of_layers);

    void SetUnitsData(double userSize, double metersSize);

    void ScanStructureForLayer(Structure* str, Point refPoint, int layer, double angle, double mag_coef,LayerForView* &layForView);
    void RecountCoordsForElement(Element* el, Point refPoint, double angle, double mag_coef, LayerForView* &layerForView);

    Structure* GetStructureByName(std::string sname);
    int GetNumOfStructures();
    double GetSizeInUserUnits();
    double GetSizeInMeters();
    void ShowInfo();

private:

    short VersionNumber;//header
    //bgnlib??
    //libdirsize
    std::string LibName;
    double sizeInUserUnits;
    double sizeInMeters;

    //Header part
    std::vector<Structure> structures;


};

#endif /* GDSIIDESIGN_H */

