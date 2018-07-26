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

#include "inc/GDSIIModel/GDSIIStructure/Structure.h"
#include <vector>
#include "inc/GUI/LayerForView.h"
#include <QtCore>
#include <memory>
#include <set>
#include "inc/GDSIIGeometry/Primitives/GDSIIPoint.h"

class GDSIIDesign {
public:
    GDSIIDesign();
    ~GDSIIDesign();

    void AddStructure(const GDSIIStructure &structure);
    std::shared_ptr<LayerForView> GetLayerForView(int layer);
    void GetLayerForView(int layer, std::shared_ptr<LayerForView> &layerForView);
    std::shared_ptr<LayerForView> GetFullDesignLayerForView();

    void SetUnitsData(double userSize, double metersSize);

    void ScanStructureForLayer(const GDSIIStructure &str, const GDSIIPoint &refPoint, int layer, double angle, double mag_coef,std::shared_ptr<LayerForView> &layForView);
    void RecountCoordsForElement(const std::shared_ptr<GDSIIElement> &el, const GDSIIPoint &refPoint, double angle, double mag_coef, std::shared_ptr<LayerForView> &layerForView);

    std::shared_ptr<GDSIIStructure> GetStructureByName(const std::string &sname);
    int GetNumOfStructures();
    double GetSizeInUserUnits();
    double GetSizeInMeters();
    void ShowInfo();

    void SaveLayer(const short &layer);
    std::set<short> GetLayersSet() const;
private:

    short VersionNumber;//header
    //bgnlib??
    //libdirsize
    std::string LibName;
    double sizeInUserUnits;
    double sizeInMeters;

    //Header part
    std::vector<GDSIIStructure> structures;
    std::set<short> _layerSet;

};

#endif /* GDSIIDESIGN_H */

