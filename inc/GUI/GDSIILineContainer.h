#ifndef LINECONTAINER_H
#define LINECONTAINER_H
#include <QtCore>
#include "inc/GDSIIGeometry/Primitives/GDSIILine.h"

typedef std::vector<GDSIILine>::const_iterator constLineContainerIt;
class GDSIILineContainer
{
public:

    GDSIILineContainer();
    std::vector<GDSIILine>& GetArray();
    int GetAmount();
    void AddLine(GDSIILine line);
    int GetAreaWidth()  const;
    int GetAreaHeight() const;
    int GetBottomX() const;
    int GetBottomY() const;
    void SetBottomX(int x_value);
    void SetBottomY(int y_value);
    void SetAreaWidth(int width);
    void SetAreaHeight(int height);

    void PerformShift();

    //std
    constLineContainerIt Begin() const;
    constLineContainerIt End()   const;

private:
    std::vector<GDSIILine> lineArray;
    int areaWidth;
    int areaHeight;

    int bottomX;
    int bottomY;
};

#endif // LINECONTAINER_H
