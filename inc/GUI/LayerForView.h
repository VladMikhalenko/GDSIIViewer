#ifndef LAYERFORVIEW_H
#define LAYERFORVIEW_H

#include <vector>
#include "inc/GDSIIModel/GDSIIElements/Boundary.h"
#include "inc/GDSIIModel/GDSIIElements/Path.h"
#include "inc/GDSIIModel/GDSIIElements/SREF.h"
#include "inc/GDSIIModel/GDSIIElements/AREF.h"
#include "GDSIILineContainer.h"
#include "inc/LithographyTools/LineAnalyzer.h"

class LayerForView
{
    std::vector<Boundary> boundaries;
    std::vector<Path> paths;

    int layerWidth;
    int layerHeight;

    int boundCount;
    int pathCount;

public:
    LayerForView();

    int GetLayerWidth();
    int GetLayerHeight();

    int GetBoundaryAmount();
    int GetPathAmount();

    std::vector<Boundary> GetBoundaries();
    std::vector<Path> GetPaths();

    void AddBoundary(Boundary* boundary);
    void AddPath(Path* path);

    std::shared_ptr<GDSIILineContainer> GetLineContainerForArea(int x_min,int y_min,int x_max,int y_max);
    std::shared_ptr<GDSIILineContainer> GetLineContainerToDraw();
    template<class T>
    void GatherLinesFromElementForArea(const std::vector<T,std::allocator<T>> &vect, std::shared_ptr<GDSIILineContainer> &container, int area_min_x,int area_min_y, int area_max_x,int area_max_y, int &layer_min_x, int &layer_min_y, int &layer_max_x, int &layer_max_y)
    {
        LineAnalyzer analys;
        GDSIIPoint currPoint;
        GDSIIPoint nextPoint;
        GDSIILine tmpLine;
        GDSIILine lowerLine = GDSIILine(GDSIIPoint(area_min_x,area_min_y),GDSIIPoint(area_max_x,area_min_y));
        GDSIILine rightLine = GDSIILine(GDSIIPoint(area_max_x,area_min_y),GDSIIPoint(area_max_x,area_max_y));
        GDSIILine upperLine = GDSIILine(GDSIIPoint(area_max_x,area_max_y),GDSIIPoint(area_min_x,area_max_y));
        GDSIILine leftLine  = GDSIILine(GDSIIPoint(area_min_x,area_max_y),GDSIIPoint(area_min_x,area_min_y));
        for(size_t i=0;i<vect.size();i++)
        {
            T el=vect[i];
            auto firstPoint = el.GetPointAt(0);
            layer_max_x = firstPoint.GetX()>layer_max_x ? firstPoint.GetX() : layer_max_x;
            layer_min_x = firstPoint.GetX()<layer_min_x ? firstPoint.GetX() : layer_min_x;
            layer_max_y = firstPoint.GetY()>layer_max_y ? firstPoint.GetY() : layer_max_y;
            layer_min_y = firstPoint.GetY()<layer_min_y ? firstPoint.GetY() : layer_min_y;

            currPoint = firstPoint;//GDSIIPoint(firstPoint.GetX(),firstPoint.GetY());
            for(int j=1;j<el.GetAmountOfPoints();j++)
            {
                std::vector<GDSIIPoint> pointsToCheck;
                pointsToCheck.reserve(2);
                GDSIIPoint lwCross,rCross,uCross,ltCross;
                nextPoint = el.GetPointAt(j);//GDSIIPoint(el.GetPointAt(j).GetX(),el.GetPointAt(j).GetY());//el_points[j].GetX(),el_points[j].GetY());
                const bool isCurrIn = analys.CheckPointBelongToArea(currPoint,area_min_x,area_min_y,area_max_x,area_max_y);
                const bool isNextIn = analys.CheckPointBelongToArea(nextPoint,area_min_x,area_min_y,area_max_x,area_max_y);
                tmpLine.SetPoints(currPoint, nextPoint);
                bool isLowerCross = analys.GetCrossPoint(tmpLine,lowerLine,lwCross);
                bool isRightCross = analys.GetCrossPoint(tmpLine,rightLine,rCross);
                bool isUpperCross = analys.GetCrossPoint(tmpLine,upperLine,uCross);
                bool isLeftCross  = analys.GetCrossPoint(tmpLine,leftLine ,ltCross);
                isRightCross = ((isLowerCross && isRightCross && (lwCross == rCross)) || (isUpperCross && isRightCross && (uCross == rCross))) ?
                            false : isRightCross;
                isLeftCross  = ((isLowerCross && isLeftCross && (lwCross == ltCross)) || (isUpperCross && isLeftCross && (uCross == ltCross))) ?
                            false : isLeftCross;

                if((isCurrIn && !isNextIn) || (!isCurrIn && isNextIn))
                {
                    GDSIIPoint cross = isLowerCross ? lwCross :
                                       isRightCross ? rCross  :
                                       isUpperCross ? uCross  : ltCross;
                    isCurrIn ? tmpLine.SetP2(cross) : tmpLine.SetP1(cross);
                    pointsToCheck.push_back(cross);
                }
                else if(isCurrIn && isNextIn)
                {
                    pointsToCheck.push_back(nextPoint);
                }
                else if(!isCurrIn && !isNextIn)
                {
                    if(isLowerCross && isUpperCross)
                    {
                        tmpLine.SetPoints(lwCross, uCross);
                        pointsToCheck.push_back(lwCross);
                        pointsToCheck.push_back(uCross);
                    }
                    else if(isLowerCross && isRightCross)
                    {
                        tmpLine.SetPoints(lwCross, rCross);
                        pointsToCheck.push_back(lwCross);
                        pointsToCheck.push_back(rCross);
                    }
                    else if(isLowerCross && isLeftCross)
                    {
                        tmpLine.SetPoints(lwCross, ltCross);
                        pointsToCheck.push_back(lwCross);
                        pointsToCheck.push_back(ltCross);
                    }
                    else if(isRightCross && isUpperCross)
                    {
                        tmpLine.SetPoints(rCross,uCross);
                        pointsToCheck.push_back(rCross);
                        pointsToCheck.push_back(uCross);
                    }
                    else if(isRightCross && isLeftCross)
                    {
                        tmpLine.SetPoints(rCross,ltCross);
                        pointsToCheck.push_back(rCross);
                        pointsToCheck.push_back(ltCross);
                    }
                    else if(isUpperCross && isLeftCross)
                    {
                        tmpLine.SetPoints(uCross,ltCross);
                        pointsToCheck.push_back(uCross);
                        pointsToCheck.push_back(ltCross);
                    }
                }
                for(auto it = pointsToCheck.begin(); it!=pointsToCheck.end();it++)
                {
                    layer_max_x = it->GetX() > layer_max_x ? it->GetX() : layer_max_x;
                    layer_min_x = it->GetX() < layer_min_x ? it->GetX() : layer_min_x;

                    layer_max_y = it->GetY() > layer_max_y ? it->GetY() : layer_max_y;
                    layer_min_y = it->GetY() < layer_min_y ? it->GetY() : layer_min_y;
                }

                if(!pointsToCheck.empty())
                {
                    container->AddLine(GDSIILine(tmpLine.GetP1(),tmpLine.GetP2()));//GDSIILine(currPoint,nextPoint));
                    pointsToCheck.clear();
                }

                currPoint=nextPoint;
            }
        }
    }

    void ClearData();

};

#endif // LAYERFORVIEW_H
