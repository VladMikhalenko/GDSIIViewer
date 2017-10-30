#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QObject>
#include <QWidget>
#include "LineContainer.h"
class DrawingArea: public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = 0);
    void SetLineContainer(LineContainer* cont);
    void SetNetStep(int step);

    void SetGlobalWidth(int width);
    void SetGlobalHeight(int height);
    void SetWindowToProjectCoef(double value);
private:
    double scaleValue;
    double scrollHorizontalValue;
    double scrollVerticalValue;

    double winToProjCoef;

    int GlobalWidth;
    int GlobalHeight;

    int netStep;
    LineContainer container;

    void paintEvent(QPaintEvent* event);
    void DrawNet(QPainter *painter);
    void DrawLine(QPainter* painter,QLine line);
    void DrawBorders(QPainter* painter);
    void DrawRectangle(QPainter* painter,QRect rectangle);
private slots:
    void HorizontalScrollValueChanged(int value);
    void VerticalScrollValueChanged(int value);
    void ScaleValueChanged(double value);


};

#endif // DRAWINGAREA_H
