#include "inc/LithographyTools/LineAnalyzer.h"
#include "math.h"
#include "inc/MathTools/FunctionProvider.h"
#include "inc/GUI/GDSIILineContainer.h"

LineAnalyzer::LineAnalyzer()
{

}

LineType LineAnalyzer::GetLineType(const GDSIILine &line)
{
    if(line.GetP1().GetX()==line.GetP2().GetX() &&
       line.GetP1().GetY()!=line.GetP2().GetY())
    {
        return VERTICAL;
    }
    else if(line.GetP1().GetX()!=line.GetP2().GetX() &&
            line.GetP1().GetY()==line.GetP2().GetY())
    {
        return HORIZONTAL;
    }
    else if(line.GetP1().GetX() < line.GetP2().GetX() &&
            line.GetP1().GetY() < line.GetP2().GetY())
    {
        return DIAGONAL_ASC;
    }
    else if(line.GetP1().GetX() > line.GetP2().GetX() &&
            line.GetP1().GetY() > line.GetP2().GetY())
    {
        return DIAGONAL_DESC;
    }
    else return UNDEFINED_LINE;
}

bool LineAnalyzer::CanAnalyzeLines(const GDSIILine &l1, const GDSIILine &l2, int allowedDist)
{
    if(l1==l2)
        return false;
    if(GetLineType(l1)==GetLineType(l2) && GetLineType(l1)!=UNDEFINED_LINE)
    {
        int x11=l1.GetP1().GetX();
        int x12=l1.GetP2().GetX();

        int x21=l2.GetP1().GetX();
        int x22=l2.GetP2().GetX();

        int y11=l1.GetP1().GetY();
        int y12=l1.GetP2().GetY();

        int y21=l2.GetP1().GetY();
        int y22=l2.GetP2().GetY();
        int actualDist=0;
        //TROUBLE WITH ALLOWED DISTANCE -> THERE A THRESHOLD VALUE WHEN ALGORYTHM BEGINS TO LET FAR LOCATED LINES TO COOPERATE
        switch(GetLineType(l1))
        {
            case HORIZONTAL:
                actualDist=y11>y21?y11-y21:y21-y11;
                return ((x11<=x21 && x12 >=x21) || (x11<=x22 && x12 >=x22)  ||
                        (x21<=x11 && x22 >=x11) || (x21<=x12 && x22 >=x12)) &&
                        (actualDist<=allowedDist);
            case VERTICAL:
                actualDist=x11>x21?x11-x21:x21-x11;
                return ((y11<=y21 && y12 >=y21) || (y11<=y22 && y12 >=y22)  ||
                        (y21<=y11 && y22 >=y11) || (y21<=y12 && y22 >=y12)) &&
                        (actualDist<=allowedDist);
            default:
                return false;
        }

    }
    else return false;
}

int LineAnalyzer::GetDistanceBetween(const GDSIILine &l1, const GDSIILine &l2, LineType type)
{
    if(GetLineType(l1)!=GetLineType(l2) || l1==l2 || type==UNDEFINED_LINE)
        return -1;
    switch (type)
    {
        case HORIZONTAL:
            return l2.GetP1().GetY()>l1.GetP1().GetY()?
                        l2.GetP1().GetY()-l1.GetP1().GetY():
                        l1.GetP1().GetY()-l2.GetP1().GetY();

        case VERTICAL:
            return l2.GetP1().GetX()>l1.GetP1().GetX()?
                        l2.GetP1().GetX()-l1.GetP1().GetX():
                        l1.GetP1().GetX()-l2.GetP1().GetX();
        default:
            return -1;
    }
}
int LineAnalyzer::GetLineLength(const GDSIILine &line)
{
    switch(GetLineType(line))
    {
        case HORIZONTAL:
            return abs(line.GetP1().GetX()-line.GetP2().GetX());
        case VERTICAL:
            return abs(line.GetP1().GetY()-line.GetP2().GetY());
        default: return -1;
    }
}

void LineAnalyzer::ParseLine(const GDSIILine &line,int &left, int &right, int &bottom, int &top)
{
    int x1=line.GetP1().GetX();
    int x2=line.GetP2().GetX();

    int y1=line.GetP1().GetY();
    int y2=line.GetP2().GetY();

    switch(GetLineType(line))
    {
        case HORIZONTAL:
            left=x1<x2?x1:x2;
            right=x1>x2?x1:x2;
            bottom=top=y1;
            break;
        case VERTICAL:
            bottom=y1<y2?y1:y2;
            top=y1>y2?y1:y2;
            left=right=x1;
            break;
        default:
            break;
    }
    return;
}

GDSIILine LineAnalyzer::GetMiddlePath(const GDSIILine &l1, const GDSIILine &l2, int allowedDistance)
{
    int leftX,rightX,bottomY,topY;
    if(CanAnalyzeLines(l1,l2,allowedDistance))
    {
        LineType lType=GetLineType(l1);
        int dist=GetDistanceBetween(l1,l2,lType);
        int halfDist=dist/2;
        int l1Left,l1Right,l1Bottom,l1Top,l2Left,l2Right,l2Bottom,l2Top;
        ParseLine(l1,l1Left,l1Right,l1Bottom,l1Top);
        ParseLine(l2,l2Left,l2Right,l2Bottom,l2Top);

        switch(lType)
        {
            case HORIZONTAL:
                bottomY=topY=l1Bottom>l2Bottom?l1Bottom-halfDist:l2Bottom-halfDist;
                leftX=l1Left<l2Left?l1Left:l2Left;//l1Left+halfDist:l2Left+halfDist;
                rightX=l1Right<l2Right?l1Right:l2Right;//l1Right-halfDist:l2Right-halfDist;
                break;
            case VERTICAL:
                leftX=rightX=l1Left>l2Left?l1Left-halfDist:l2Left-halfDist;
                bottomY=l1Bottom<l2Bottom?l1Bottom:l2Bottom;//l1Bottom+halfDist:l2Bottom+halfDist;
                topY=l1Top<l2Top?l1Top:l2Top;//l1Top-halfDist:l2Top-halfDist;
                break;
            default:
                leftX=0;
                rightX=1;
                bottomY=0;
                topY=1;
                break;
        }
    }
    else
    {
        //create UNDEFINED type line
        leftX=0;
        rightX=1;
        bottomY=0;
        topY=1;
    }
    return GDSIILine(leftX,bottomY,rightX,topY);
}
void LineAnalyzer::GetMiddlePath(const std::vector<GDSIILine> &v, std::vector<GDSIILine> &res,int allowedDistance)
{
    if(v.size()<2 || allowedDistance<=0)
        return;
    for(unsigned i=0;i<v.size();i++)
    {
        for(unsigned j=i+1;j<v.size();j++)
        {
            GDSIILine mid=GetMiddlePath(v[i],v[j],allowedDistance);
            if(GetLineType(mid)!=UNDEFINED_LINE)
                res.emplace_back(mid);
        }
    }
}

CodeType LineAnalyzer::GetCode(const GDSIILine &l1)
{
    LineType lType = GetLineType(l1);
    if(lType == VERTICAL)
        return VERTIC_CODE;
    else if(lType == HORIZONTAL)
        return HORIZO_CODE;
    else
        return ERROR_CODE;
}
CodeType LineAnalyzer::GetCode(const GDSIILine &l1, const GDSIILine &l2)
{
    if(l1==l2)
        return GetCode(l1);
    LineType t1 = GetLineType(l1);
    LineType t2 = GetLineType(l2);
    if(t1 == t2)
        return ERROR_CODE;
    else if(t1 == VERTICAL && t2 == HORIZONTAL)
    {
        int top1,bot1,left1,right1;
        int top2,bot2,left2,right2;
        top1 = bot1 = left1 = right1 = 0;
        top2 = bot2 = left2 = right2 = 0;
        ParseLine(l1,left1,right1,bot1,top1);
        ParseLine(l2,left2,right2,bot2,top2);
        GDSIIPoint cross;
        if(GetCrossPoint(l1,l2,cross))
        {
            int cx = cross.GetX();
            int cy = cross.GetY();
            if(cy == top1 && cy == top2)
            {
                if(cx == left1 && cx == left2)
                {
                    return L_UP_CORNER;
                }
                else if(cx == right1 && cx == right2)
                {
                    return R_UP_CORNER;
                }
            }
            else if(cy == bot1 && cy == bot2)
            {
                if(cx == left1 && cx == left2)
                {
                    return L_LW_CORNER;
                }
                else if(cx == right1 && cx == right2)
                {
                    return R_LW_CORNER;
                }
            }
            else
                return ERROR_CODE;
        }
        else
            return ERROR_CODE;
    }
    else if(t1 == DIAGONAL_ASC && t2 == DIAGONAL_DESC)
    {
        int top1,bot1,left1,right1;
        int top2,bot2,left2,right2;
        top1 = bot1 = left1 = right1 = 0;
        top2 = bot2 = left2 = right2 = 0;
        ParseLine(l1,left1,right1,bot1,top1);
        ParseLine(l2,left2,right2,bot2,top2);
        GDSIIPoint cross;
        if(GetCrossPoint(l1,l2,cross))
        {
            int cx = cross.GetX();
            int cy = cross.GetY();
            if(cy == top1 && cy == top2)
            {
                if(cx > left1 && cx < right2)
                {
                    return ASC_DESC_U;
                }
                else
                {
                    return ERROR_CODE;
                }
            }
            else if(cy == bot1 && cy == bot2)
            {
                if(cx > left1 && cx < right2)
                {
                    return ASC_DESC_D;
                }
                else
                {
                    return ERROR_CODE;
                }
            }
            else if(cx == left1 && cx == left2)
            {
                if(cx < top1 && cx > bot2)
                {
                    return ASC_DESC_L;
                }
                else
                {
                    return ERROR_CODE;
                }
            }
            else if(cx == right1 && cx ==right2)
            {
                if(cx < top1 && cx > bot2)
                {
                    return ASC_DESC_R;
                }
                else
                {
                    return ERROR_CODE;
                }
            }
            else
                return ERROR_CODE;
        }
        else
            return ERROR_CODE;
    }
    else if(t1 == HORIZONTAL && t2 == VERTICAL ||
            t1 == DIAGONAL_DESC && t2 == DIAGONAL_ASC)
    {
        return GetCode(l2,l1);
    }
}

CodeType LineAnalyzer::GetCode(const GDSIILine &l1, const GDSIILine &l2, const GDSIILine &l3)
{

}

bool LineAnalyzer::IsPointOnLine(const GDSIIPoint &p, const GDSIILine &l)
{
    int x = p.GetX();
    int y = p.GetY();
    int x1 = l.GetP1().GetX();
    int y1 = l.GetP1().GetY();
    int x2 = l.GetP2().GetX();
    int y2 = l.GetP2().GetY();

    return  ((x1 <= x && x2 >= x) || (x2 <= x && x1 >= x)) &&
            ((y1 <= y && y2 >= y) || (y2 <= y && y1 >= y));
}

bool LineAnalyzer::GetCrossPoint(const GDSIILine &l1, const GDSIILine &l2, GDSIIPoint &cross)
{
    if(l1==l2)
        return false;
    int x1 = l1.GetP1().GetX();
    int y1 = l1.GetP1().GetY();
    int x2 = l1.GetP2().GetX();
    int y2 = l1.GetP2().GetY();

    int x3 = l2.GetP1().GetX();
    int y3 = l2.GetP1().GetY();
    int x4 = l2.GetP2().GetX();
    int y4 = l2.GetP2().GetY();

    int x = FunctionProvider::GetLineCrossX(x1,y1,x2,y2,x3,y3,x4,y4);
    int y = FunctionProvider::GetLineCrossY(x3,y3,x4,y4,x);
    cross.SetX(x);
    cross.SetY(y);
    bool belongL1 = IsPointOnLine(GDSIIPoint(x,y),l1);
    bool belongL2 = IsPointOnLine(GDSIIPoint(x,y),l2);
    return belongL1 && belongL2;//(((x1<=x) && (x2>=x) && (x3<=x) && (x4>=x)) || ((y1<=y) && (y2>=y) && (y3<=y) && (y4>=y)));
}

GDSIIPoint LineAnalyzer::GetLeastPoint(const GDSIILine &l) const
{
    if(l.GetP1().GetX() < l.GetP2().GetX())
    {
        return l.GetP1();
    }
    else if(l.GetP1().GetX() == l.GetP2().GetX())
    {
        if(l.GetP1().GetY() < l.GetP2().GetY())
        {
            return l.GetP1();
        }
        else
        {
            return l.GetP2();
        }
    }
    else
    {
        return l.GetP2();
    }
    //return (l.GetP1().GetX() <= l.GetP2().GetX()) && (l.GetP1().GetY() <= l.GetP2().GetY()) ? l.GetP1() : l.GetP2();
}

GDSIIPoint LineAnalyzer::GetGreatPoint(const GDSIILine &l) const
{
    if(l.GetP1().GetX() > l.GetP2().GetX())
    {
        return l.GetP1();
    }
    else if(l.GetP1().GetX() == l.GetP2().GetX())
    {
        if(l.GetP1().GetY() > l.GetP2().GetY())
        {
            return l.GetP1();
        }
        else
        {
            return l.GetP2();
        }
    }
    else
    {
        return l.GetP2();
    }
}

bool LineAnalyzer::CompareLines(const GDSIIPoint &p1, const GDSIIPoint &p2) const
{
    if(p1.GetX() == p2.GetX())
    {
        return p1.GetY() < p2.GetY();
    }
    else
    {
        return p1.GetX() < p2.GetX();
    }
}

void LineAnalyzer::SortLineContainer(GDSIILineContainer &container)
{
    /* из каждой линии выбирается точка с наименьшими координатами
     * далее сравниваются координаты Х и если они равны то сравниваются Y
     */
    auto begin = container.GetArray().begin();
    auto end = container.GetArray().end();
    std::sort(begin,end,
    [&container, this](const GDSIILine &l1, const GDSIILine &l2)
    {
        GDSIIPoint p1 = GetLeastPoint(l1);
        GDSIIPoint p2 = GetLeastPoint(l2);
        GDSIIPoint pg1 = GetGreatPoint(l1);
        GDSIIPoint pg2 = GetGreatPoint(l2);
        return p1 != p2 ? CompareLines(p1,p2) :
                          CompareLines(pg1,pg2);
    });
}
