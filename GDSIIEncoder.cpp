#include "GDSIIEncoder.h"

void GDSIIEncoder::SortContainer(GDSIILineContainer &cont)
{
    /* из каждой линии выбирается точка с наименьшими координатами
     * далее сравниваются координаты Х и если они равны то сравниваются Y
     */
    auto begin = cont.GetArray().begin();
    auto end = cont.GetArray().end();
    std::sort(begin,end,
    [&cont, this](const GDSIILine &l1, const GDSIILine &l2)
    {
        GDSIIPoint p1 = lineAnalizer.GetLeastPoint(l1);
        GDSIIPoint p2 = lineAnalizer.GetLeastPoint(l2);
        GDSIIPoint pg1 = lineAnalizer.GetGreatPoint(l1);
        GDSIIPoint pg2 = lineAnalizer.GetGreatPoint(l2);
        return p1 != p2 ? lineAnalizer.CompareLines(p1,p2) :
                          lineAnalizer.CompareLines(pg1,pg2);
    });
}
//написав генератор коду для простих ліній
//зараз думаю над сортуванням ліній
//далі буду використовувати метод для вибору ліній для вказаної області
void GDSIIEncoder::ConstructMap(const GDSIILineContainer &cont)
{

    int posCounter = 0;
    int pointsCounter = 0;
    auto begin = const_cast<GDSIILineContainer&>(cont).GetArray().begin();
    auto end = const_cast<GDSIILineContainer&>(cont).GetArray().end();
    locMap.clear();//пустой указатель какого-то...
    for(;begin != end; ++begin)
    {
        printf("Consider: [%d,%d|%d,%d]\n",begin->GetP1().GetX(),begin->GetP1().GetY(),begin->GetP2().GetX(),begin->GetP2().GetY());
        GDSIIPoint leastPoint =lineAnalizer.GetLeastPoint(*begin);
        int x_coord = leastPoint.GetX();
        auto search = locMap.find(x_coord);

        if(search != locMap.end())
        {
            auto& value = locMap[leastPoint.GetX()];
            value = ENCODE_RIGHT_IN_INT32(value,++pointsCounter);
        }
        else
        {
            pointsCounter = 0;
            int value = ENCODE_TWO_IN_INT32(posCounter,pointsCounter);
            locMap.insert(std::pair<int,int>(leastPoint.GetX(),value));
        }
        ++posCounter;
    };
}
void GDSIIEncoder::Encode(std::string fileName, GDSIILineContainer &cont)
{
    SortContainer(cont);
    ConstructMap(cont);
    std::for_each(locMap.begin(),locMap.end(),
    [](std::map<int,int>::value_type pair)
    {
        printf("[%d] = %d",pair.first, pair.second);
    });
}
