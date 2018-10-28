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
    int _size;
    GDSIISuperPixel(GDSIIPoint init,int size):_initPoint(init),_size(size){}
    GDSIISuperPixel(int x1, int y1,int size):_initPoint(GDSIIPoint(x1,y1)),_size(size){}
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
    void PostEncodingAnalysis(std::vector<CodeType> &codes);

public:
    static GDSIIDesignEncoder& GetInstance()
    {
        static GDSIIDesignEncoder _instance;
        return _instance;
    }
    std::string Encode(const GDSIILineContainer &container, int pixelSize);

private://trash
    std::map<int,int> _locationMap;
    void ConstructLocationMap(GDSIILineContainer& container);
    void PrintMap() const;
    std::map<int,int> GetLocationMap() const;

};

#endif // GDSIIDESIGNENCODER_H
