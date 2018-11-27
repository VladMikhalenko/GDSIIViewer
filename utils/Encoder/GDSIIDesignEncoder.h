#ifndef GDSIIDESIGNENCODER_H
#define GDSIIDESIGNENCODER_H

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "inc/LithographyTools/LineAnalyzer.h"
#include "inc/GUI/GDSIILineContainer.h"

#include <iostream>
#define ENCODE_TWO_IN_INT32(left,right)  ((left<<16)|(right&65535))
#define ENCODE_LEFT_IN_INT32(base,value) ((base&65535)|(value<<16))
#define ENCODE_RIGHT_IN_INT32(base,value)((base&4294901760)|(value))
#define DECODE_LEFT_IN_INT32(value) (value>>16)
#define DECODE_RIGHT_IN_INT32(value)(value&65535)

struct GDSIISuperPixel
{
    GDSIIPoint _initPoint;
    int        _size;
    CodeType   _code;
    bool       _isCritical;
    std::set<GDSIILine*> _relatedLines;
    GDSIISuperPixel(GDSIIPoint init,int size, CodeType code = EMPTY):
        _initPoint(init)
      ,_size(size)
      ,_code(code)
      ,_isCritical(false)
      ,_relatedLines(){}
    GDSIISuperPixel(int x1, int y1,int size, CodeType code = EMPTY):
        _initPoint(GDSIIPoint(x1,y1))
      ,_size(size)
      ,_code(code)
      ,_isCritical(false)
      ,_relatedLines(){}
    int GetSize()
    {
        return _size;
    }
    int GetXLimit() const
    {
        return _initPoint.GetX()+_size;
    }
    int GetYLimit() const
    {
        return _initPoint.GetY()+_size;
    }
    GDSIILine GetVerticalMid() const
    {
        return GDSIILine(_initPoint.GetX()+_size/2,_initPoint.GetY(),_initPoint.GetX()+_size/2,_initPoint.GetY()+_size);
    }
    GDSIILine GetHorizontalMid() const
    {
        return GDSIILine(_initPoint.GetX(),_initPoint.GetY()+_size/2,_initPoint.GetX()+_size,_initPoint.GetY()+_size/2);
    }
    void AddRelatedLine(GDSIILine &line)
    {
        _isCritical = true;
        _relatedLines.insert(&line);
    }
    bool CompareCriticalLines(const GDSIISuperPixel& pix)
    {
        if(_relatedLines.size() == pix._relatedLines.size())
        {
            for(std::set<GDSIILine*>::iterator it = _relatedLines.begin(); it!=_relatedLines.end();it++)
            {
                if(pix._relatedLines.find(*it)==pix._relatedLines.end())
                    return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
};

struct ValidityPair
{
    enum Direction {HOR, VER, INV};
    GDSIISuperPixel* curr;
    GDSIISuperPixel* prev;
    GDSIISuperPixel* uCurr;
    GDSIISuperPixel* uPrev;
    Direction _direct;

    ValidityPair(GDSIISuperPixel *current,
                 GDSIISuperPixel *previous  = nullptr,
                 GDSIISuperPixel *uCurrent  = nullptr,
                 GDSIISuperPixel *uPrevious = nullptr,
                 Direction direction = HOR):
        curr(current)
       ,prev(previous)
       ,uCurr(uCurrent)
       ,uPrev(uPrevious)
       ,_direct(direction){}
    bool isShrinkNeeded()
    {
        if(curr && prev)
        {
            bool isPrevCrit = prev->_isCritical;
            bool isCurrCrit = curr->_isCritical;
            if(!isPrevCrit && !isCurrCrit)
                return false;
            else if(_direct == HOR || _direct == VER)
            {
                return (isPrevCrit && isCurrCrit) && prev->CompareCriticalLines(*curr);
            }
        }
        return false;

    }
    void Shrink()
    {
        if(isShrinkNeeded())
        {
            CodeType prevCode = prev->_code;
            CodeType currCode = curr->_code;
            if(_direct == HOR)
            {
                if(prevCode == currCode)
                {
                    if((prevCode == L_LW_CORNER) ||
                       (prevCode == L_UP_CORNER))
                    {
                        prev->_code = EMPTY;
                    }
                    else if((prevCode == R_LW_CORNER) ||
                            (prevCode == R_UP_CORNER))
                    {
                        curr->_code = EMPTY;
                    }
                    else if(prevCode == VERTIC_CODE)
                    {
                        if((!uPrev && !uCurr) || ((uPrev->_code == EMPTY) && (uCurr->_code ==EMPTY)))
                        {
                            prev->_code = EMPTY;
                        }
                        else
                        {
                            if(uCurr->_code == EMPTY)
                            {
                                curr->_code = EMPTY;
                            }
                            else if(uPrev->_code == EMPTY)
                            {
                                prev->_code = EMPTY;
                            }
                        }
                    }
                }
            }
            else if(_direct == VER)
            {
                if(prevCode == currCode)
                {
                    if((prevCode == L_LW_CORNER) ||
                       (prevCode == R_LW_CORNER))
                    {
                        prev->_code = EMPTY;
                    }
                    else if((prevCode == L_UP_CORNER) ||
                            (prevCode == R_UP_CORNER))
                    {
                        curr->_code = EMPTY;
                    }
                    else if(prevCode == HORIZO_CODE)
                    {
                        if((!uPrev && !uCurr) || ((uPrev->_code == EMPTY) && (uCurr->_code ==EMPTY)))
                        {
                            prev->_code = EMPTY;
                        }
                        else
                        {
                            if(uCurr->_code == EMPTY)
                            {
                                curr->_code = EMPTY;
                            }
                            else if(uPrev->_code == EMPTY)
                            {
                                prev->_code = EMPTY;
                            }
                        }
                    }
                }
            }
        }


    }
    void ShrinkV2()
    {
        if(isShrinkNeeded())
        {
            CodeType prevCode = prev->_code;
            CodeType currCode = curr->_code;
            if(_direct == HOR)
            {
                bool areUnderAvailable = uCurr && uPrev;
                if(prevCode == currCode)
                {
                    if(prevCode == L_LW_CORNER)
                    {
                        curr->_code = HORIZO_CODE;//prev->_code = EMPTY;
                    }
                    else if(prevCode == L_UP_CORNER)
                    {
                        if(areUnderAvailable)
                        {
                            CodeType uCurrCode = uCurr->_code;
                            CodeType uPrevCode = uPrev->_code;
                            if((uCurrCode == VERTIC_CODE) ||
                               (uCurrCode == L_LW_CORNER) ||
                               (uCurrCode == R_LW_CORNER))
                            {
                                prev->_code = EMPTY;
                            }
                            else  if((uPrevCode == VERTIC_CODE) ||
                                     (uPrevCode == L_LW_CORNER) ||
                                     (uPrevCode == R_LW_CORNER))
                            {
                                curr->_code = HORIZO_CODE;
                            }
                        }
                        else
                        {
                            curr->_code = HORIZO_CODE;
                        }
                    }
                    else if(prevCode == R_LW_CORNER)
                    {
                        prev->_code = HORIZO_CODE;//curr->_code = EMPTY;
                    }
                    else if(prevCode == R_UP_CORNER)
                    {
                        if(areUnderAvailable)
                        {
                            CodeType uCurrCode = uCurr->_code;
                            CodeType uPrevCode = uPrev->_code;
                            if((uCurrCode == VERTIC_CODE) ||
                               (uCurrCode == L_LW_CORNER) ||
                               (uCurrCode == R_LW_CORNER))
                            {
                                prev->_code = HORIZO_CODE;
                            }
                            else  if((uPrevCode == VERTIC_CODE) ||
                                     (uPrevCode == L_LW_CORNER) ||
                                     (uPrevCode == R_LW_CORNER))
                            {
                                curr->_code = EMPTY;
                            }
                        }
                        else
                        {
                            prev->_code = HORIZO_CODE;
                        }
                    }
                    else if(prevCode == Z_DEFAULT)
                    {
                        curr->_code = HORIZO_CODE;
                    }
                    else if(prevCode == S_DEFAULT)
                    {
                        curr->_code = HORIZO_CODE;
                    }
                    else if(prevCode == VERTIC_CODE)
                    {
                        if(!areUnderAvailable)
                        {
                            prev->_code = EMPTY;
                        }
                        else
                        {
                            CodeType uCurrCode = uCurr->_code;
                            CodeType uPrevCode = uPrev->_code;
                            if((uCurrCode == EMPTY) &&
                               (uPrevCode == EMPTY))
                            {
                                prev->_code = EMPTY;
                            }
                            else if((uCurrCode == VERTIC_CODE) ||
                                    (uCurrCode == L_LW_CORNER) ||
                                    (uCurrCode == R_LW_CORNER))
                            {
                                prev->_code = EMPTY;
                            }
                            else if((uPrevCode == VERTIC_CODE) ||
                                    (uPrevCode == L_LW_CORNER) ||
                                    (uPrevCode == R_LW_CORNER))
                            {
                                curr->_code = EMPTY;
                            }
                            else if(uCurr->_code == EMPTY)
                            {
                                curr->_code = EMPTY;
                            }
                            else if(uPrev->_code == EMPTY)
                            {
                                prev->_code = EMPTY;
                            }
                        }
                    }
                }
                else
                {
                    if((prevCode == Z_ROTATED) && (currCode == R_LW_CORNER))
                    {
                        curr->_code = EMPTY;//prev->_code = L_UP_CORNER;
                    }
                    else if((currCode == Z_ROTATED) && (prevCode == L_UP_CORNER))
                    {
                        prev->_code = EMPTY;
                    }
                    else if((currCode == S_ROTATED) && (prevCode == L_LW_CORNER))
                    {
                        prev->_code = EMPTY;
                    }
                    else if((prevCode == S_ROTATED) && (currCode == R_UP_CORNER))
                    {
                        curr->_code = EMPTY;
                    }
                }
            }
            else if(_direct == VER)
            {
                if(prevCode == currCode)
                {
                    if(prevCode == L_LW_CORNER)
                    {
                        prev->_code = EMPTY;
                    }
                    else if(prevCode == R_LW_CORNER)
                    {
                        prev->_code = EMPTY;
                        if(uPrev)
                        {
                            uPrev->_code = EMPTY;
                        }
                    }
                    else if(prevCode == L_UP_CORNER)
                    {
                        curr->_code = EMPTY;
                    }
                    else if(prevCode == R_UP_CORNER)
                    {
                        curr->_code = EMPTY;
                        if(uCurr)
                        {
                            uCurr->_code = EMPTY;
                        }
                    }
                    else if(prevCode == Z_ROTATED)
                    {
                        prev->_code = VERTIC_CODE;
                    }
                    else if(prevCode == S_ROTATED)
                    {
                        prev->_code = VERTIC_CODE;
                    }
                    else if(prevCode == HORIZO_CODE)
                    {
                        if((!uPrev && !uCurr) || ((uPrev->_code == EMPTY) && (uCurr->_code ==EMPTY)))
                        {
                            prev->_code = EMPTY;
                        }
                        else
                        {
                            if(uCurr->_code == EMPTY)
                            {
                                curr->_code = EMPTY;
                            }
                            else if(uPrev->_code == EMPTY)
                            {
                                prev->_code = EMPTY;
                            }
                        }
                    }
                }
                else
                {
                    if(uPrev && uCurr)
                    {
                        CodeType uPrevCode = uPrev->_code;
                        CodeType uCurrCode = uCurr->_code;
                        if(uPrevCode == currCode)
                        {
                            if(currCode == L_LW_CORNER)
                            {
                               uPrev->_code = EMPTY;
                            }
                            else if(currCode == R_LW_CORNER)
                            {
                                uPrev->_code = EMPTY;
                            }
                            else if(currCode == L_UP_CORNER)
                            {
                                curr->_code = EMPTY;
                            }
                            else if(currCode == R_UP_CORNER)
                            {
                                curr->_code = EMPTY;
                            }
                            else if(currCode == HORIZO_CODE)
                            {
                                curr->_code = EMPTY;
                            }
                        }
//                        else if(uCurrCode == prevCode)
//                        {
//                            if(prevCode == L_LW_CORNER)
//                            {
//                                uCurrCode->_code = EMPTY;
//                            }
//                            else if(prevCode == R_LW_CORNER)
//                            {
//                                uCurrCode->_code = EMPTY;
//                            }
//                            else if(prevCode == L_UP_CORNER)
//                            {
//                                prev->_code = EMPTY;
//                            }
//                            else if(prevCode == R_UP_CORNER)
//                            {
//                                curr->_code = EMPTY;
//                            }
//                            else if(prevCode == HORIZO_CODE)
//                            {
//                                curr->_code = EMPTY;
//                            }
//                        }
                    }
                }
            }
        }

    }
};

class Validator
{
    public:
    static void tryExecuteValidation(std::vector<GDSIISuperPixel>& pixels, size_t blockNum)
    {
        const size_t size = pixels.size();
        if(size > 1)
        {
            std::vector<GDSIISuperPixel>::iterator currIt = pixels.end() - 1;
            std::vector<GDSIISuperPixel>::iterator prevIt = currIt-1;

            if(size < blockNum)//(currIt-pixels.begin())%blockNum != 0)
            {
                ValidityPair horPair(&(*currIt),&(*prevIt));
                //horPair.Shrink();
                horPair.ShrinkV2();
            }
            else if(size%blockNum == 1)
            {
                prevIt = currIt - blockNum;
                ValidityPair verPair(&(*currIt),&(*prevIt));
                //verPair.Shrink();
                verPair.ShrinkV2();
            }
            else// if(size%blockNum > 1)
            {
                std::vector<GDSIISuperPixel>::iterator uCurrIt = currIt - blockNum;
                std::vector<GDSIISuperPixel>::iterator uPrevIt = prevIt - blockNum;
                ValidityPair horz(&(*currIt),&(*prevIt),&(*uCurrIt),&(*uPrevIt),ValidityPair::HOR);
                ValidityPair vert(&(*currIt),&(*uCurrIt),&(*prevIt),&(*uPrevIt),ValidityPair::VER);
//                horz.Shrink();
//                vert.Shrink();
                horz.ShrinkV2();
                vert.ShrinkV2();
            }
        }
    }
};

struct GDSIILineRefenceSet
{
    std::set<GDSIILine*> _set;
    GDSIILineRefenceSet():_set(){}
    void InsertLine(GDSIILine &line)
    {
        _set.insert(&line);
    }
};

//ERROR_CODE  = -1,
//EMPTY       = 0,
//HORIZO_CODE = 1,
//VERTIC_CODE = 2,
//R_UP_CORNER = 3,
//L_UP_CORNER = 4,
//R_LW_CORNER = 5,
//L_LW_CORNER = 6,
//Z_DEFAULT   = 7,
//Z_ROTATED   = 8,
//S_DEFAULT   = 9,
//S_ROTATED   = 10,
//ASC_CODE    = 11,// '/'
//DESC_CODE   = 12,// '\'
//ASC_DESC_U  = 13,// '^'
//ASC_DESC_D  = 14,// 'v'
//ASC_DESC_L  = 15,// '<'
//ASC_DESC_R  = 16,// '>'
class GDSIIDesignEncoder
{
    std::map<CodeType,char> _charMap = {
        {ERROR_CODE ,'X'},
        {EMPTY      ,'0'},
        {HORIZO_CODE,'1'},
        {VERTIC_CODE,'2'},
        {R_UP_CORNER,'3'},
        {L_UP_CORNER,'4'},
        {R_LW_CORNER,'5'},
        {L_LW_CORNER,'6'},
        {Z_DEFAULT  ,'7'},
        {Z_ROTATED  ,'8'},
        {S_DEFAULT  ,'9'},
        {S_ROTATED  ,'a'},
        {ASC_CODE   ,'b'},
        {DESC_CODE  ,'c'},
        {ASC_DESC_U ,'d'},
        {ASC_DESC_D ,'e'},
        {ASC_DESC_L ,'f'},
        {ASC_DESC_R ,'g'}
    };
    //singleton methods
    GDSIIDesignEncoder();
    ~GDSIIDesignEncoder();
    GDSIIDesignEncoder(const GDSIIDesignEncoder&);
    GDSIIDesignEncoder& operator=(const GDSIIDesignEncoder&);

    LineAnalyzer _lineAnalizer;

    std::map<int,GDSIILineRefenceSet> _xCoordMap;
    std::map<int,GDSIILineRefenceSet> _yCoordMap;

    int bottomX;
    int bottomY;
    int topX;
    int topY;

    inline int GetEncodingAreaWidth() { return topX - bottomX;}
    inline int GetEncodingAreaHeight(){ return topY - bottomY;}
    void ConstructReferencedMap(GDSIILineContainer& container);
    void ExtractLinesForSuperPixel(const GDSIISuperPixel& pix, std::set<GDSIILine *> &vect);

    void PrintReferencedMap() const;
    void PrepareData(GDSIILineContainer& container);
    void PostEncodingAnalysis(std::vector<GDSIISuperPixel> &codes, size_t areaWidth);

    void ExtractLinesForSuperPixel(GDSIISuperPixel& pix, std::set<GDSIILine*> &lineSet);

public:
    static GDSIIDesignEncoder& GetInstance()
    {
        static GDSIIDesignEncoder _instance;
        return _instance;
    }
    std::string Encode(const GDSIILineContainer &container, int pixelSize);
    std::string EncodeSPApproach(const GDSIILineContainer &container, int pixelSize);

private://trash
    std::map<int,int> _locationMap;
    void ConstructLocationMap(GDSIILineContainer& container);
    void PrintMap() const;
    std::map<int,int> GetLocationMap() const;

};

#endif // GDSIIDESIGNENCODER_H
