#include "GDSIIDesignEncoder.h"
#include <iostream>
GDSIIDesignEncoder::GDSIIDesignEncoder():
    _lineAnalizer(),
    _locationMap(),
    _xCoordMap(),
    bottomX(INT32_MAX),
    bottomY(INT32_MAX),
    topX(INT32_MIN),
    topY(INT32_MIN)
{}
GDSIIDesignEncoder::~GDSIIDesignEncoder()
{}
void GDSIIDesignEncoder::PrepareData(GDSIILineContainer &container)
{
    //ConstructLocationMap(container);
    //PrintMap();
    //_lineAnalizer.SortLineContainer(container);
    ConstructReferencedMap(container);
    PrintReferencedMap();
    //PrintReferencedMap();
}

void GDSIIDesignEncoder::Encode(const GDSIILineContainer &container, int pixelSize)
{
    std::vector<CodeType> codes;
    std::set<GDSIILine*> lines;
    PrepareData(const_cast<GDSIILineContainer&>(container));
    GDSIISuperPixel pixel(GDSIIPoint(bottomX,bottomY),pixelSize);
    int encW = GetEncodingAreaWidth();
    int encH = GetEncodingAreaHeight();

    if(pixel.GetSize() > encH || pixel.GetSize() > encW)
    {
        std::cout<<"Encoding failed: pixel does not fit container\n";
        return;
    }
    unsigned step = pixel._size;
    codes.reserve((encW/step)*(encH/step));
    for(int y = bottomY; y < topY; y+=step)
    {
        for(int x = bottomX; x < topX; x+=step)
        {
            if(x == 30)
            {
                std::cout<<30<<std::endl;
            }
            lines.clear();
            ExtractLinesForSuperPixel(GDSIISuperPixel(x,y,step),lines);
            CodeType code = EMPTY;
            switch(lines.size())
            {
                case 0:
                {
                    code = EMPTY;
                }break;
                case 1:
                {
                    const GDSIILine* lp = *lines.begin();
                    code = _lineAnalizer.GetCode(*lp);//_lineAnalizer.GetCode(*lines[0]);
                }break;
                case 2:
                {
                    std::set<GDSIILine*>::iterator it = lines.begin();
                    GDSIILine l1 = **it;
                    GDSIILine l2 = **(++it);
                    code = _lineAnalizer.GetCode(l1,l2);
                }break;
                default: code = ERROR_CODE;
            }
            codes.push_back(code);
        }
    }
    unsigned blockN = encW/step;
    std::string log="";
    for(auto it = codes.end(); it>codes.begin(); it-=blockN)
    {
        int pos = codes.size()-(codes.end()-(it-blockN));
        for(unsigned i = pos; i < pos+blockN;i++)
        {
            log+=_charMap[codes[i]];
        }
        log+='\n';
    }
    std::cout<<log;
}

void GDSIIDesignEncoder::ExtractLinesForSuperPixel(const GDSIISuperPixel &pix, std::set<GDSIILine *> &container)
{
    std::cout<<"\tScanning lines for SP("<<pix._initPoint.GetX()<<","<<pix._initPoint.GetY()<<") Size:"<<pix._size<<std::endl;
    for(int i = pix._initPoint.GetX(); i<=pix.GetXLimit();i++)
    {
        auto search = _xCoordMap.find(i);
        if(search != _xCoordMap.end())
        {
            GDSIILineRefenceSet& set = search->second;
            for(auto data:set._set)
            {
                if(_lineAnalizer.LineBelongToSuperPixel(pix,*data))
                {
                    container.insert(data);
                }
            }
        }
    }
    std::cout<<"\t\tFound "<<container.size()<<" lines on X...\n \t\tScanning Y coords..."<<std::endl;
    for(int i = pix._initPoint.GetY(); i<=pix.GetYLimit();i++)
    {
        auto search = _yCoordMap.find(i);
        if(search != _yCoordMap.end())
        {
            GDSIILineRefenceSet& set = search->second;
            for(auto data:set._set)
            {
                if(_lineAnalizer.LineBelongToSuperPixel(pix,*data))
                {
                    container.insert(data);
                }
            }
        }
    }
    std::cout<<"Total lines detected: "<<container.size()<<std::endl;
}

void GDSIIDesignEncoder::ConstructLocationMap(GDSIILineContainer &container)
{
    _locationMap.clear();
    int posCounter = 0;
    int pointsCounter = 1;
    auto begin = container.GetArray().begin();
    auto end = container.GetArray().end();
    for(;begin != end; ++begin)
    {
        GDSIIPoint leastPoint =_lineAnalizer.GetLeastPoint(*begin);
        int x_coord = leastPoint.GetX();
        auto search = _locationMap.find(x_coord);

        if(search != _locationMap.end())
        {
            auto& value = _locationMap[leastPoint.GetX()];
            value = ENCODE_RIGHT_IN_INT32(value,++pointsCounter);
        }
        else
        {
            pointsCounter = 1;
            int value = ENCODE_TWO_IN_INT32(posCounter,pointsCounter);
            _locationMap.insert(std::pair<int,int>(leastPoint.GetX(),value));
        }
        ++posCounter;
    };
}

void GDSIIDesignEncoder::ConstructReferencedMap(GDSIILineContainer &container)
{
    _xCoordMap.clear();
    _yCoordMap.clear();
    std::cout<<"Constructing referenced map...\n";
    auto begin = container.GetArray().begin();
    auto end = container.GetArray().end();
    for(;begin != end; ++begin)
    {
        int x1 = begin->GetP1().GetX();
        int x2 = begin->GetP2().GetX();
        int y1 = begin->GetP1().GetY();
        int y2 = begin->GetP2().GetY();
        _xCoordMap[x1].InsertLine(*begin);
        _xCoordMap[x2].InsertLine(*begin);

        _yCoordMap[y1].InsertLine(*begin);
        _yCoordMap[y2].InsertLine(*begin);

        int minX = x1 <= x2 ? x1 : x2;
        int minY = y1 <= y2 ? y1 : y2;
        int maxX = minX == x1 ? x2 : x1;
        int maxY = minY == y1 ? y2 : y1;
        bottomX = minX < bottomX ? minX : bottomX;
        bottomY = minY < bottomY ? minY : bottomY;
        topX = maxX > topX ? maxX : topX;
        topY = maxY > topY ? maxY : topY;
    };
    std::cout<<"Referenced map constructed!\n";
    std::cout<<"Arrea borders calculated! bot("<<bottomX<<","<<bottomY<<") top("<<
               topX<<","<<topY<<")\n";
}

std::map<int,int> GDSIIDesignEncoder::GetLocationMap() const
{
    return _locationMap;
}

void GDSIIDesignEncoder::PrintMap() const
{
    std::cout<<"<----Location map---->\n";
    for(auto it = _locationMap.begin(); it !=_locationMap.end();it++)
    {
        std::cout<<"["<<it->first<<"] = "<<DECODE_LEFT_IN_INT32(it->second)<<"|"<<DECODE_RIGHT_IN_INT32(it->second)<<std::endl;
    }
}

void GDSIIDesignEncoder::PrintReferencedMap() const
{
    std::cout<<"<------BGN References map------>\n";
    for(auto it = _xCoordMap.begin(); it !=_xCoordMap.end();it++)
    {
        std::cout<<"["<<it->first<<"] = ";
        for(auto vit=it->second._set.begin(); vit!=it->second._set.end();vit++)
        {
            std::cout<<"\t["<<(*vit)->GetP1().GetX()<<","<<
                              (*vit)->GetP1().GetY()<<"]["<<
                              (*vit)->GetP2().GetX()<<","<<
                              (*vit)->GetP2().GetY()<<"]\n";
        }
    }
    std::cout<<"<------END References map------>\n";
}
