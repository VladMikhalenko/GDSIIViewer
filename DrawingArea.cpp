#include "DrawingArea.h"
#include <QPainter>
#include <QPicture>
#include <QDebug>
#include <QMessageBox>

DrawingArea::DrawingArea(QWidget* parent):QWidget(parent)
{
    scaleValue=1;
    GlobalWidth=0;
    GlobalHeight=0;
    scrollHorizontalValue=0;
    scrollVerticalValue=0;
    SetNetStep(5);
}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;

    //brush.setColor(Qt::green);
    //brush.setStyle(Qt::CrossPattern);

    painter.setPen(pen);
    painter.setBrush(brush);

    QSize widgetSize=this->size();
    QTransform moveTo0_0_Pr(1,0,0,1,-GlobalWidth/2,-GlobalHeight/2);
    QTransform moveToCenter_Pr(1,0,0,1,GlobalWidth/2,GlobalHeight/2);

    QTransform scrollMat(1,0,0,1,scrollHorizontalValue,scrollVerticalValue);
    QTransform axisYMat(1,0,0,1,0,GlobalHeight);//(winToProjCoef));//height());

    int newZeroX=container.GetBottomX()>0?-container.GetBottomX():container.GetBottomX();
    int newZeroY=container.GetBottomY()>0?-container.GetBottomY():container.GetBottomY();
    //qDebug()<<"newBottomX"<<newZeroX<<" new bottomY"<<newZeroY;

    //QTransform moveAXIS(1,0,0,1,newZeroX,newZeroY);

    double heightMoveValue=widgetSize.height()/2-(GlobalHeight/2)/winToProjCoef;
    double widthMoveValue=widgetSize.width()/2-(GlobalWidth/2)/winToProjCoef;
    //qDebug()<<"H move:"<<heightMoveValue<<" and W move:"<<widthMoveValue<<" winCOEF:"<<winToProjCoef;
    //qDebug()<<"Layer size:"<<container.GetAreaWidth()<<"x"<<container.GetAreaHeight();
    QTransform moveToCenter=QTransform(1,0,0,1,widthMoveValue,heightMoveValue);
    QTransform scaleMat(scaleValue,0,0,scaleValue,0,0);
    QTransform coefMat(1/winToProjCoef,0,0,1/winToProjCoef,0,0);
    QTransform result;
    result=axisYMat*moveTo0_0_Pr*scaleMat*moveToCenter_Pr*scrollMat*coefMat*moveToCenter;
    painter.setTransform(result);
    painter.setRenderHint(QPainter::Antialiasing,true);
    if(container.GetAmount()>0)
    {
        //DrawNet(&painter);
        DrawBorders(&painter);
        //qDebug()<<"Scale value:"<<scaleValue;
        pen.setWidth(winToProjCoef>=1?winToProjCoef/scaleValue:winToProjCoef);
        pen.setColor(Qt::black);
        painter.setPen(pen);

        for(int i=0;i<container.GetAmount();i++)
            DrawLine(&painter,container.GetArray()[i]);
    }
    //QString str=QString("scale %1 & horScroll %2 & vertScroll %3").arg(QString::number(scaleValue),QString::number(scrollHorizontalValue),QString::number(scrollVerticalValue));
    //painter.drawText(QRect(QPoint(widgetSize.width()/2,(-widgetSize.height()/2)-50),widgetSize),str);
    //painter.drawText(QRect(QPoint(0,(-GlobalHeight/2)),QSize(GlobalWidth/winToProjCoef,GlobalHeight/winToProjCoef)),str);


}

void DrawingArea::DrawBorders(QPainter *painter)
{
    QPen pen;
    pen.setWidth(winToProjCoef>=1?3*winToProjCoef/scaleValue:winToProjCoef*3);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    DrawLine(painter,QLine(0,0,GlobalWidth,0));
    DrawLine(painter,QLine(0,0,0,GlobalHeight));
    DrawLine(painter,QLine(0,GlobalHeight,GlobalWidth,GlobalHeight));
    DrawLine(painter,QLine(GlobalWidth,0,GlobalWidth,GlobalHeight));
}

void DrawingArea::DrawNet(QPainter* painter){
    QPen pen;
    pen.setWidth(winToProjCoef>=1?winToProjCoef/scaleValue:winToProjCoef);
    pen.setColor(Qt::lightGray);
    painter->setPen(pen);

    for(int i=0;i<GlobalWidth;i+=netStep)//this->width();i+=netStep)////
    {
        //qDebug()<<"I draw line ("<<i<<","<<0<<")"<<"("<<i<<GlobalHeight;
        //painter->drawLine(i,0,i,-height());//
        painter->drawLine(i,0,i,-GlobalHeight);//-GlobalHeight);//-height());//
    }
    for(int i=0;i<GlobalHeight;i+=netStep)//this->height();i+=netStep)//
    {
        //qDebug()<<"I draw line ("<<0<<","<<i<<")"<<"("<<i<<" "<<GlobalHeight;
        //painter->drawLine(0,-i,width(),-i);//
        painter->drawLine(0,-i,GlobalWidth,-i);//-i,GlobalWidth,-i);//width(),-i);//
    }
    //qDebug()<<"LINE:"<<0<<","<<0<<"|"<<GlobalWidth/winToProjCoef<<","<<0;

    //painter->drawLine(0,0,GlobalWidth,GlobalHeight);
    //painter->drawLine(0,GlobalHeight,GlobalWidth,GlobalHeight);
    //painter->drawLine(0,0,0,GlobalHeight);
}
void DrawingArea::DrawLine(QPainter* painter,QLine line){
    //qDebug()<<"I'm drawing line:["<<x_p1<<","<<y_p1<<"]|"<<"["<<x_p2<<","<<y_p2<<"]";
    painter->drawLine(QLine(line.p1().x(),-line.p1().y(),line.p2().x(),-line.p2().y()));

    //else qDebug()<<"I'm not drawing line:["<<x_p1<<","<<y_p1<<"]|"<<"["<<x_p2<<","<<y_p2<<"]";

}

void DrawingArea::HorizontalScrollValueChanged(int value)
{
    double scrollDist=GlobalWidth*scaleValue-width()*winToProjCoef;
    //qDebug()<<"GW(Sc)-GW"<<GlobalWidth*scaleValue<<"-"<<width()*winToProjCoef<<"="<<scrollDist;
    scrollHorizontalValue=scrollDist>0?scrollDist/2-value:0;//scrollDist>0?scrollDist/2-value:0;//((width()*scaleValue-width())/2-value);//
    //qDebug()<<"Srcoll HOR VALUE="<<scrollDist/2<<"-"<<value<<scrollDist/2-value;
    repaint();
}
void DrawingArea::VerticalScrollValueChanged(int value){

    double scrollDist=GlobalHeight*scaleValue-height()*winToProjCoef;
    scrollVerticalValue=scrollDist>0?scrollDist/2-value:0;//((height()*scaleValue-height())/2-value);//
    repaint();
}


void DrawingArea::ScaleValueChanged(double value)//void DrawingArea::ScaleValueChanged(int value)
{
    scaleValue=value;
    //qDebug()<<"Width: "<<width()<<"Scale Value"<<scaleValue;
    repaint();
}

void DrawingArea::SetLineContainer(LineContainer *cont){
    container=*cont;
    SetGlobalHeight(container.GetAreaHeight());
    SetGlobalWidth(container.GetAreaWidth());
    QLine* lines=container.GetArray();
    int bottomX=-container.GetBottomX();//container.GetBottomX()>0?-container.GetBottomX():container.GetBottomX();
    int bottomY=-container.GetBottomY();//container.GetBottomY()>0?-container.GetBottomY():container.GetBottomY();
    for(int i=0;i<container.GetAmount();i++)
    {
        //bad solution
        int nX1=lines[i].x1()+bottomX;
        int nX2=lines[i].x2()+bottomX;
        int nY1=lines[i].y1()+bottomY;
        int nY2=lines[i].y2()+bottomY;
        lines[i].setLine(nX1,nY1,nX2,nY2);
        /*qDebug()<<"["<<i<<"] Line:["<<
                  lines[i].p1().x()-bottomX<<","<<
                  lines[i].p1().y()-bottomY<<"] & ["<<
                  lines[i].p2().x()-bottomX<<","<<
                  lines[i].p2().y()-bottomY<<"]";
        */
        qDebug()<<"["<<i<<"] Line:["<<
                          lines[i].p1().x()<<","<<
                          lines[i].p1().y()<<"] & ["<<
                          lines[i].p2().x()<<","<<
                          lines[i].p2().y()<<"]";
    }
}

void DrawingArea::SetNetStep(int step){
    netStep=step;
}

void DrawingArea::SetGlobalHeight(int height){
    GlobalHeight=height;
}
void DrawingArea::SetGlobalWidth(int width){
    GlobalWidth=width;
}

void DrawingArea::SetWindowToProjectCoef(double value)
{
    winToProjCoef=value;
}
