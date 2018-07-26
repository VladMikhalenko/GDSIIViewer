#include "GDSIIDesignEncoder.h"
#include <iostream>
GDSIIDesignEncoder::GDSIIDesignEncoder():
    _lineAnalizer(),
    _locationMap(),
    _map(),
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
    std::vector<GDSIILine*> lines;
    PrepareData(const_cast<GDSIILineContainer&>(container));
    GDSIISuperPixel pixel(GDSIIPoint(0,0),pixelSize);
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
            lines.clear();
            GetLinesInSuperPixel(GDSIISuperPixel(x,y,step),lines);
            CodeType code = EMPTY;
            switch(lines.size())
            {
                case 0:
                {
                    code = EMPTY;
                }break;
                case 1:
                {
                    code = _lineAnalizer.GetCode(*lines[0]);
                }break;
                case 2:
                {
                    code = _lineAnalizer.GetCode(*lines[0],*lines[1]);
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
    //зробити вивод лога для переdshrb
}

void GDSIIDesignEncoder::GetLinesInSuperPixel(const GDSIISuperPixel &pix, std::vector<GDSIILine *> &vect)
{
    for(int i = pix._initPoint.GetX(); i<=pix.GetXLimit();i++)
    {
        auto search = _map.find(i);
        if(search != _map.end())
        {
            GDSIILineRefenceSet& set = search->second;
            for(auto data:set._set)
            {
                bool isP1In = data->GetP1().GetY() <= pix._initPoint.GetY()+pix._size &&
                        data->GetP1().GetY() >= pix._initPoint.GetY();
                bool isP2In = data->GetP2().GetY() <= pix._initPoint.GetY()+pix._size &&
                        data->GetP2().GetY() >= pix._initPoint.GetY();
                if(isP1In || isP2In)
                {
                    vect.push_back(data);
                }
            }
        }
    }
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
    _map.clear();
    std::cout<<"Constructing referenced map...\n";
    auto begin = container.GetArray().begin();
    auto end = container.GetArray().end();
    for(;begin != end; ++begin)
    {
        int x1 = begin->GetP1().GetX();
        int x2 = begin->GetP2().GetX();
        int y1 = begin->GetP1().GetY();
        int y2 = begin->GetP2().GetY();
        _map[x1].InsertLine(*begin);
        _map[x2].InsertLine(*begin);
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
    for(auto it = _map.begin(); it !=_map.end();it++)
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
