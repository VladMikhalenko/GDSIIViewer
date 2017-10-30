#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DrawingArea.h"
#include <QDebug>
#include <QtCore>
#include <QtWidgets>
#include <QFileDialog>
#include <cmath>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dArea=new DrawingArea(this);
    dArea->setFixedWidth(ui->horizontalScrollBar->width());
    dArea->setFixedHeight(ui->verticalScrollBar->height());
    ui->vertLayout->addWidget(dArea);
    this->setFixedHeight(this->height());
    this->setFixedWidth(this->width());
    ResetWindowBorders();
    designLoaded=false;
    ui->mainToolBar->setVisible(false);
    ui->statusBar->setEnabled(false);
    currentLayer=0;
    //Large project exapmle 800x900
    /*
    SetProjectWidth(800);
    SetProjectHeight(900);
    dArea->SetGlobalWidth(ProjectWidth);
    dArea->SetGlobalHeight(ProjectHeight);
    
    CalculateWindowToProjectCoef();

    QLine p1(100,100,300,650);
    QLine p2(300,650,400,300);
    QLine p3(400,300,550,300);
    QLine p4(550,300,550,100);
    QLine p5(550,100,250,100);

    QLine p6(500,850,500,400);
    QLine p7(500,400,750,400);
    QLine p8(750,400,750,850);
    QLine p9(750,850,500,850);

    LineContainer* lines=new LineContainer();
    lines->AddLine(p1);
    lines->AddLine(p2);
    lines->AddLine(p3);
    lines->AddLine(p4);
    lines->AddLine(p5);
    lines->AddLine(p6);
    lines->AddLine(p7);
    lines->AddLine(p8);
    lines->AddLine(p9);
    */
    // wide example 1200x200
    /*SetProjectWidth(1200);
    SetProjectHeight(200);
    dArea->SetGlobalWidth(ProjectWidth);
    dArea->SetGlobalHeight(ProjectHeight);
    CalculateWindowToProjectCoef();

    QLine p1(250,50,250,150);
    QLine p2(250,150,850,150);
    QLine p3(850,150,850,100);
    QLine p4(850,100,650,100);
    QLine p5(650,100,650,50);
    QLine p6(650,50,250,50);

    LineContainer* lines=new LineContainer();
    lines->AddLine(p1);
    lines->AddLine(p2);
    lines->AddLine(p3);
    lines->AddLine(p4);
    lines->AddLine(p5);
    lines->AddLine(p6);
    */
    //если стороны фигуры соотносятся высота к ширине с коеф 0.66 2/3, 4/6 ....
    // small example 300x200
    /*SetProjectWidth(300);
    SetProjectHeight(200);
    dArea->SetGlobalWidth(ProjectWidth);
    dArea->SetGlobalHeight(ProjectHeight);
    CalculateWindowToProjectCoef();

    QLine p1(50,50,250,150);
    QLine p2(50,150,250,50);
    QLine p3(150,150,150,50);

    LineContainer* lines=new LineContainer();
    lines->AddLine(p1);
    lines->AddLine(p2);
    lines->AddLine(p3);
    */
    // small example 200x300
    /*SetProjectWidth(200);
    SetProjectHeight(300);
    dArea->SetGlobalWidth(ProjectWidth);
    dArea->SetGlobalHeight(ProjectHeight);
    CalculateWindowToProjectCoef();

    QLine p1(100,300,100,0);
    QLine p2(50,200,150,200);
    QLine p3(150,200,150,150);
    QLine p4(50,200,50,150);

    LineContainer* lines=new LineContainer();
    lines->AddLine(p1);
    lines->AddLine(p2);
    lines->AddLine(p3);
    lines->AddLine(p4);
    */
    /*
    SetProjectWidth(60);
    SetProjectHeight(10);
    dArea->SetGlobalWidth(ProjectWidth);
    dArea->SetGlobalHeight(ProjectHeight);
    CalculateWindowToProjectCoef();

    QLine p1(5,5,25,15);
    QLine p2(5,15,25,5);
    QLine p3(15,15,15,5);

    LineContainer* lines=new LineContainer();
    lines->AddLine(p1);
    lines->AddLine(p2);
    lines->AddLine(p3);
    */
    /*
    //rectangle
    QLine left(400,100,400,200);
    QLine top(400,200,600,200);
    QLine right(600,200,600,100);
    QLine bottom(600,100,400,100);
    //path
    QLine pt1(0,0,50,100);
    QLine pt2(50,100,50,300);
    QLine pt3(50,300,200,300);

    //polygon
    QLine f1(150,100,300,100);
    QLine f2(300,100,300,130);
    QLine f3(300,130,200,130);
    QLine f4(200,130,200,180);
    QLine f5(200,180,150,180);
    QLine f6(150,180,150,100);

    QLine cl(0,dArea->height()-31,300,dArea->height()-31);


    LineContainer* lines=new LineContainer();
    lines->AddLine(left);
    lines->AddLine(top);
    lines->AddLine(right);
    lines->AddLine(bottom);
    lines->AddLine(pt1);
    lines->AddLine(pt2);
    lines->AddLine(pt3);
    lines->AddLine(f1);
    lines->AddLine(f2);
    lines->AddLine(f3);
    lines->AddLine(f4);
    lines->AddLine(f5);
    lines->AddLine(f6);
    lines->AddLine(cl);
    */
    /*  621x341
    SetProjectWidth(621);
    SetProjectHeight(341);
    dArea->SetGlobalWidth(ProjectWidth);
    dArea->SetGlobalHeight(ProjectHeight);

    CalculateWindowToProjectCoef();

    QLine p1(100,100,300,650);
    QLine p2(300,650,400,300);
    QLine p3(400,300,550,300);
    QLine p4(550,300,550,100);
    QLine p5(550,100,250,100);

    QLine p6(500,850,500,400);
    QLine p7(500,400,750,400);
    QLine p8(750,400,750,850);
    QLine p9(750,850,500,850);

    LineContainer* lines=new LineContainer();
    lines->AddLine(p1);
    lines->AddLine(p2);
    lines->AddLine(p3);
    lines->AddLine(p4);
    lines->AddLine(p5);
    lines->AddLine(p6);
    lines->AddLine(p7);
    lines->AddLine(p8);
    lines->AddLine(p9);

    */

    //dArea->SetLineContainer(lines);

    //ui->spbZoom->setFocusPolicy(Qt::NoFocus);
    //ui->spbLayer->setFocusPolicy(Qt::NoFocus);
    //QObject::connect(ui->spbZoom,SIGNAL(valueChanged(int)),dArea,SLOT(ScaleValueChanged(int)));
    QObject::connect(ui->spbZoom,SIGNAL(valueChanged(int)),this,SLOT(ZoomValueChanged(int)));
    QObject::connect(ui->spbZoom,SIGNAL(valueChanged(int)),this,SLOT(CalculateScrolls(int)));

    QObject::connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(BtnOkClick()));

    QObject::connect(ui->btnScann,SIGNAL(clicked()),this,SLOT(BtnScannClick()));

    QObject::connect(ui->spbLayer,SIGNAL(valueChanged(int)),this,SLOT(LayerValueChanged(int)));

    QObject::connect(this,SIGNAL(ZoomValueUpdated(double)),dArea,SLOT(ScaleValueChanged(double)));
    //QObject::connect(this,SIGNAL(ZoomValueUpdated(double)),this,SLOT(CalculateWindowPoints(double)));

    QObject::connect(ui->verticalScrollBar,SIGNAL(valueChanged(int)),dArea,SLOT(VerticalScrollValueChanged(int)));
    QObject::connect(ui->horizontalScrollBar,SIGNAL(valueChanged(int)),dArea,SLOT(HorizontalScrollValueChanged(int)));

    QObject::connect(ui->verticalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(VerticalScrollChanged(int)));
    QObject::connect(ui->horizontalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(HorizontalScrollChanged(int)));

    QObject::connect(ui->rbOne,SIGNAL(clicked(bool)),this,SLOT(RadioOneChanged()));
    QObject::connect(ui->rbSeveral,SIGNAL(clicked(bool)),this,SLOT(RadioSeveralChanged()));



    ui->spbZoom->setMaximum(10000);
    ui->spbZoom->setMinimum(100);
    ui->spbLayer->setMaximum(63);
    ui->verticalScrollBar->setMaximum(0);
    ui->horizontalScrollBar->setMaximum(0);

    ui->btnOK->setEnabled(false);
    ui->spbLayer->setEnabled(false);
    ui->spbZoom->setEnabled(false);
    //CalculateScrolls(ui->spbZoom->value());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete design;
    delete layerForView;
    delete dArea;
}

void MainWindow::paintEvent(QPaintEvent *event){
}
void MainWindow::CalculateScrolls(int value)
{
    double checkVal=value/100.0;
    double sizeWidthScale=ProjectWidth*checkVal;
    double sizeHeightScale=ProjectHeight*checkVal;
    //qDebug()<<"Size width with scale:"<<sizeWidthScale;
    //qDebug()<<"Size height with scale:"<<sizeHeightScale;

    ui->horizontalScrollBar->setMaximum(sizeWidthScale>dArea->width()*winProjCoef?sizeWidthScale-dArea->width()*winProjCoef:0);//sizeWidthScale-dArea->width():0);
    ui->horizontalScrollBar->valueChanged(ui->horizontalScrollBar->value());
    //qDebug()<<"HorMAX:"<<ui->horizontalScrollBar->maximum();
    ui->verticalScrollBar->setMaximum(sizeHeightScale>dArea->height()*winProjCoef?sizeHeightScale-dArea->height()*winProjCoef:0);//(ProjectHeight-width)*2:0);//sizeHeightScale-dArea->height():0);
    ui->verticalScrollBar->valueChanged(ui->verticalScrollBar->value());
    //qDebug()<<"GOAL:::::=>"<<sizeHeightScale<<" h2:"<<dArea->height()*winProjCoef<<"="<<sizeHeightScale-dArea->height()*winProjCoef;//*2;
    //qDebug()<<"VerMAX:"<<ui->verticalScrollBar->maximum();
    //qDebug()<<"HorMAX:"<<ui->horizontalScrollBar->maximum();
}
void MainWindow::CalculateWindowPoints(double value){
    //qDebug()<<"HOR SCROLL VALUE:"<<horScrollValue;
    //qDebug()<<"VER SCROLL VALUE:"<<verScrollValue;

    winMinX=horScrollValue/value;
    winMinY=verScrollValue/value;

    winMaxX=dArea->width()*winProjCoef/value+winMinX;
    winMaxY=dArea->height()*winProjCoef/value+winMinY;

    qDebug()<<"Window borders:["<<winMinX<<","<<winMinY<<"], "<<"["<<winMaxX<<","<<winMaxY<<"]";
}

void MainWindow::ZoomValueChanged(int value){
    zoomCoef=ZoomConvert(value);
    //qDebug()<<"COEF value:"<<zoomCoef;
    emit ZoomValueUpdated(zoomCoef);
}
//Calculate window position in global World
void MainWindow::HorizontalScrollChanged(int value){
    horScrollValue=value;
    //qDebug()<<"Window position in pixels:["<<horScrollValue<<","<<verScrollValue<<"]";
    if(designLoaded)
        CalculateWindowPoints(zoomCoef);
    //PrepareLineContainerForDrawing();
    //repaint();
}
void MainWindow::VerticalScrollChanged(int value){
    int max=ui->verticalScrollBar->maximum();
    verScrollValue=abs(value-max);
    //qDebug()<<"MAX:"<<max<<" Vert val:"<<verScrollValue;
    //qDebug()<<"VerScrVal:"<<verScrollValue;
    //qDebug()<<"Window position in pixels:["<<horScrollValue<<","<<verScrollValue<<"]";
    if(designLoaded)
        CalculateWindowPoints(zoomCoef);
    //PrepareLineContainerForDrawing();
}

void MainWindow::LayerValueChanged(int value){
    currentLayer=value;
    //LayerForView* l4v=design->GetLayerForView(value);
    //LineContainer* cont=l4v->GetLineContainerForArea(winMinX,winMinY,winMaxX,winMaxY);
    //dArea->SetLineContainer(cont);
}

void MainWindow::GetNewLayerFromDesign()
{
    ui->rbOne->isChecked()?layerForView=design->GetLayerForView(currentLayer):layerForView=design->GetSeveralLayersForView(currentLayer);
    //qDebug()<<"Layer size:"<<layerForView->GetLayerWidth()<<"x"<<layerForView->GetLayerHeight();
}

void MainWindow::PrepareLineContainerForDrawing()
{
    if(layerForView!=0)
    {
        //добавить учет позиции окна
        LineContainer* cont=layerForView->GetLineContainerForArea(winMinX,winMinY,winMaxX,winMaxY);
        qDebug()<<"Layer size:"<<cont->GetAreaWidth()<<"x"<<cont->GetAreaHeight();

        SetProjectWidth(cont->GetAreaWidth());
        SetProjectHeight(cont->GetAreaHeight());
        CalculateWindowToProjectCoef();
        dArea->SetLineContainer(cont);
    }
    else
    { //throw AnError();

    }
}

void MainWindow::BtnOkClick(){
    ResetWindowBorders();
    GetNewLayerFromDesign();
    PrepareLineContainerForDrawing();
    ui->spbZoom->setValue(100);
    repaint();
}
void MainWindow::BtnScannClick()
{
    scanner->ScannLayer(10,21);
}

double MainWindow::ZoomConvert(int value)
{
    return value/100.0;
}

void MainWindow::RadioOneChanged()
{
    QMessageBox::information(this,"OUUUUU","ONE WAS SELECTED");
}
void MainWindow::RadioSeveralChanged()
{
    QMessageBox::information(this,"OUUUUU","SEVERAL WAS SELECTED");
}

void MainWindow::SetProjectHeight(int height){
    ProjectHeight=height;
}
void MainWindow::SetProjectWidth(int width){
    ProjectWidth=width;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fName="";
    try
    {
        fName=QFileDialog::getOpenFileName(this,"Open File","E:/");
    }
    catch(QException ex)
    {
        QMessageBox::information(this,"Found error","Error info"+QString(ex.what()));
    }

    if(!fName.isEmpty())
    {

        QFileInfo fileInfo(fName);
        QString extension=fileInfo.suffix();
        GlobalOptions::SetFileName(fName.toStdString());
        if(extension=="txt")
        {
            GlobalOptions::SetSourceType(TEXT_SOURCE);
        }
        else GlobalOptions::SetSourceType(FILE_SOURCE);
        //if(design!=0)
        //    ClearDataBeforeLoading();
        designReader=new GDSIIDesignReader();
        designLoaded=false;
        try
        {    
            //сделать динамическую подмену имени файла источника!!
            design=designReader->MakeModel();
            if(design!=0)
            {
               designLoaded=true;
               scanner=new HotSpotScaner(design);
               QMessageBox::information(this,"Success","Design from file '"+fileInfo.baseName()+"' was successfully loaded");
               setWindowTitle("GDSIIViewer - "+fileInfo.baseName()+"."+extension);
               design->ShowInfo();
               ui->btnOK->setEnabled(true);
               ui->spbLayer->setEnabled(true);
               ui->spbZoom->setEnabled(true);
               ui->menuBar->actions()[0]->menu()->actions()[0]->setEnabled(false);
            }
            else
            {
                setWindowTitle("GDSIIViewer");
                QMessageBox::information(this,"Error","Failure while reading file '"+fileInfo.baseName()+"'");
                ui->btnOK->setEnabled(true);
                ui->spbLayer->setEnabled(true);
                ui->spbZoom->setEnabled(true);

            }


        }
        catch (QException ex)
        {
            QMessageBox::information(this,"Error occur","Error while building a design");
        }

        //QMessageBox::information(this,"Success","Design was successfully loaded");
        //QMessageBox::information(this,"File was selected",fName+" AND ext="+extension);
    }
    else
    QMessageBox::information(this,"Notification","No file was selected");
}
void MainWindow::on_actionExit_triggered()
{
    this->close();
}

//this method calculates coeficient to fit the project into a widget in form
void MainWindow::CalculateWindowToProjectCoef()
{
    if(ProjectWidth>0 && ProjectHeight>0)
    {
        winProjCoef=ProjectWidth/(double)dArea->width()>ProjectHeight/(double)dArea->height()?
                    ProjectWidth/(double)dArea->width():
                    ProjectHeight/(double)dArea->height();
        //qDebug()<<"CALC wp coef:"<<(double)winProjCoef;
        dArea->SetWindowToProjectCoef(winProjCoef);
    }
}
void MainWindow::ResetWindowBorders()
{
    winMinX=INT32_MIN;//std::numeric_limits<double>::min();
    winMinY=INT32_MIN;//std::numeric_limits<double>::min();
    winMaxX=INT32_MAX;//std::numeric_limits<double>::max();
    winMaxY=INT32_MAX;//std::numeric_limits<double>::min();

}
void MainWindow::ClearDataBeforeLoading()
{

    //problem
    if(layerForView!=0)
        layerForView->ClearData();
    //Element p=design->GetStructureByName("EXAMPLE2")->GetElementByIndex(0);
    delete design;
    delete designReader;

    layerForView=0;
    design=0;
    designReader=0;
}
