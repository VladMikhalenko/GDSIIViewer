#ifndef LINEANALYZER_H
#define LINEANALYZER_H

#include "inc/GDSIIGeometry/Primitives/GDSIILine.h"
#include <vector>
class GDSIILineContainer;
struct GDSIISuperPixel;
enum LineType{
    UNDEFINED_LINE=-1,
    VERTICAL_LINE,
    HORIZONTAL_LINE,
    DIAGONAL_ASC_LINE,
    DIAGONAL_DESC_LINE
};

enum CodeType
    {
        ERROR_CODE  = -1,
        EMPTY       = 0,
        HORIZO_CODE = 1,
        VERTIC_CODE = 2,
        R_UP_CORNER = 3,
        L_UP_CORNER = 4,
        R_LW_CORNER = 5,
        L_LW_CORNER = 6,
        ASC_CODE    = 7,// '/'
        DESC_CODE   = 8,// '\'
        ASC_DESC_U  = 9,// '^'
        ASC_DESC_D = 10,// 'v'
        ASC_DESC_L = 11,// '<'
        ASC_DESC_R = 12,// '>'
    };

class LineAnalyzer
{
    bool CanAnalyzeLines(const GDSIILine &l1, const GDSIILine &l2, int allowedDist);
public:
    LineAnalyzer();
    //Classifies line type: hor or vert
    LineType GetLineType(const GDSIILine &line);
    int GetLineLength(const GDSIILine &line);
    int GetDistanceBetween(const GDSIILine &l1, const GDSIILine &l2,LineType type);
    //Extracts borders of line
    void ParseLine(const GDSIILine &line,int &left,int &right,int &bottom,int &top);
    //Middle path methods
    GDSIILine GetMiddlePath(const GDSIILine &l1, const GDSIILine &l2, int allowedDistance);
    void GetMiddlePath(const std::vector<GDSIILine> &v, std::vector<GDSIILine> &res, int allowedDistance);

    bool GetCrossPoint(const GDSIILine &l1, const GDSIILine &l2, GDSIIPoint &cross);

    CodeType GetCode(const GDSIILine &l1);
    CodeType GetCode(const GDSIILine &l1, const GDSIILine &l2);
    CodeType GetCode(const GDSIILine &l1, const GDSIILine &l2, const GDSIILine &l3);

    bool IsPointOnLine(const GDSIIPoint &p, const GDSIILine &l);

    GDSIIPoint GetLeastPoint(const GDSIILine &l) const;
    GDSIIPoint GetGreatPoint(const GDSIILine &l) const;
    bool CompareLines(const GDSIIPoint &p1, const GDSIIPoint &p2) const;
    bool LineBelongToSuperPixel(const GDSIISuperPixel &pix, const GDSIILine &l);
    bool PointBelongToSuperPixel(const GDSIISuperPixel &pix, const GDSIIPoint &p);

    void SortLineContainer(GDSIILineContainer& container);
};

#endif // LINEANALYZER_H
