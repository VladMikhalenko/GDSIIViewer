#ifndef LINECONTAINER_H
#define LINECONTAINER_H
#include <QtCore>

class LineContainer
{
public:
    LineContainer();
    QLine* GetArray();
    int GetAmount();
    void AddLine(QLine line);
    int GetAreaWidth();
    int GetAreaHeight();
    int GetBottomX();
    int GetBottomY();
    void SetBottomX(int x_value);
    void SetBottomY(int y_value);
    void SetAreaWidth(int width);
    void SetAreaHeight(int height);

private:
    QVector<QLine> lineArray;
    int areaWidth;
    int areaHeight;

    int bottomX;
    int bottomY;
};

#endif // LINECONTAINER_H
