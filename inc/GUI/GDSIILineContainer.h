#ifndef LINECONTAINER_H
#define LINECONTAINER_H
#include <QtCore>
#include "inc/GDSIIGeometry/Primitives/GDSIILine.h"
class GDSIILineContainer
{
public:
    GDSIILineContainer();
    std::vector<GDSIILine>& GetArray();
    int GetAmount();
    void AddLine(GDSIILine line);
    int GetAreaWidth();
    int GetAreaHeight();
    int GetBottomX();
    int GetBottomY();
    void SetBottomX(int x_value);
    void SetBottomY(int y_value);
    void SetAreaWidth(int width);
    void SetAreaHeight(int height);

private:
    std::vector<GDSIILine> lineArray;
    int areaWidth;
    int areaHeight;

    int bottomX;
    int bottomY;
};

#endif // LINECONTAINER_H
