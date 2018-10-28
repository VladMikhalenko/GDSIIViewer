#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtCore>
#include <QtWidgets>
#include <QFileDialog>
#include <cmath>
#include <ctime>

#include "utils/Encoder/GDSIIDesignEncoder.h"
#include "utils/FileWriter/FileWriter.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dArea(new DrawingArea(this))
{
    ui->setupUi(this);

    dArea->setFixedWidth(ui->horizontalScrollBar->width());
    dArea->setFixedHeight(ui->verticalScrollBar->height());

    ui->vertLayout->addWidget(dArea.get());

    this->setFixedHeight(this->height());
    this->setFixedWidth(this->width());
    ResetWindowBorders();
    designLoaded=false;
    ui->mainToolBar->setVisible(false);
    ui->statusBar->setEnabled(false);
    currentLayer=0;

    //ui->spbZoom->setFocusPolicy(Qt::NoFocus);
    //ui->spbLayer->setFocusPolicy(Qt::NoFocus);
    //QObject::connect(ui->spbZoom,SIGNAL(valueChanged(int)),dArea,SLOT(ScaleValueChanged(int)));
    QObject::connect(ui->spbZoom,SIGNAL(valueChanged(int)),this,SLOT(ZoomValueChanged(int)));
    QObject::connect(ui->spbZoom,SIGNAL(valueChanged(int)),this,SLOT(CalculateScrolls(int)));

    QObject::connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(BtnOkClick()));

    QObject::connect(ui->btnScann,SIGNAL(clicked()),this,SLOT(BtnScannClick()));

    QObject::connect(ui->btnEncode,SIGNAL(clicked()),this,SLOT(btnEncodeClick()));

    QObject::connect(ui->spbLayer,SIGNAL(valueChanged(int)),this,SLOT(LayerValueChanged(int)));

    QObject::connect(ui->spbExtrLayer,SIGNAL(valueChanged(int)),this,SLOT(extractionLayerChanged(int)));

    QObject::connect(ui->spbMarker,SIGNAL(valueChanged(int)),this,SLOT(markerLayerChanged(int)));

    QObject::connect(this,SIGNAL(ZoomValueUpdated(double)),dArea.get(),SLOT(ScaleValueChanged(double)));
    //QObject::connect(this,SIGNAL(ZoomValueUpdated(double)),this,SLOT(CalculateWindowPoints(double)));

    QObject::connect(ui->verticalScrollBar,SIGNAL(valueChanged(int)),dArea.get(),SLOT(VerticalScrollValueChanged(int)));
    QObject::connect(ui->horizontalScrollBar,SIGNAL(valueChanged(int)),dArea.get(),SLOT(HorizontalScrollValueChanged(int)));

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
    ui->spbMarker->setValue(21);
    ui->spbExtrLayer->setValue(10);
    //CalculateScrolls(ui->spbZoom->value());
}

MainWindow::~MainWindow()
{
    delete ui;
//    delete design;
//    delete layerForView;
//    delete dArea;
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

    //qDebug()<<"Window borders:["<<winMinX<<","<<winMinY<<"], "<<"["<<winMaxX<<","<<winMaxY<<"]";
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

void MainWindow::extractionLayerChanged(int value)
{
    extractionLayer = value;
}

void MainWindow::markerLayerChanged(int value)
{
    markerLayer = value;
}

void MainWindow::GetNewLayerFromDesign()
{
    if(ui->rbOne->isChecked())
    {
        layerForView=design->GetLayerForView(currentLayer);
    }
    else
    {
        layerForView=design->GetFullDesignLayerForView();//GetAllDesignLayersForView();
    }
    //qDebug()<<"Layer size:"<<layerForView->GetLayerWidth()<<"x"<<layerForView->GetLayerHeight();
}

void MainWindow::PrepareLineContainerForDrawing()
{
    if(layerForView!=0)
    {
        //добавить учет позиции окна
        std::shared_ptr<GDSIILineContainer> cont=layerForView->GetLineContainerToDraw(); //GetLineContainerForArea(winMinX,winMinY,winMaxX,winMaxY);
        //qDebug()<<"Layer size:"<<cont->GetAreaWidth()<<"x"<<cont->GetAreaHeight();
        //GDSIIDesignEncoder::GetInstance().PrepareData(*cont);
        //cont->PerformShift();
        //GDSIIDesignEncoder::GetInstance().Encode(*cont,1000); MOVED TO ENCODE CLICK
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
    std::clock_t start;
    double duration;
    ResetWindowBorders();

    start=std::clock();
    GetNewLayerFromDesign();
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    qDebug()<<"Layer from design time:"<<duration<<"\n";

    start=std::clock();
    PrepareLineContainerForDrawing();
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    qDebug()<<"Prepare container time:"<<duration<<"\n";

    ui->spbZoom->setValue(100);
    repaint();
}
void MainWindow::BtnScannClick()
{
    //scanner->ScannLayer(extractionLayer,markerLayer);
    //scanner->PerformScanning(extractionLayer,markerLayer);
    scanner->ExtractMarkedAreasWithGaussAsJPG(extractionLayer,markerLayer);
}

void MainWindow::btnEncodeClick()
{
//    ResetWindowBorders();
//    GetNewLayerFromDesign();
//    std::shared_ptr<GDSIILineContainer> cont=layerForView->GetLineContainerForArea(winMinX,winMinY,winMaxX,winMaxY);
//    cont->PerformShift();
    std::vector<GDSIILineContainer> v = scanner->ExtractAllMarkedAreas(extractionLayer,markerLayer);
    for(unsigned long long i = 0; i < v.size();i++)
    {
        auto item = v[i];
        item.PerformShift();
        std::string code = GDSIIDesignEncoder::GetInstance().Encode(item,20);
        FileWriter::GetInstance().WriteStringToFile("Code_"+std::to_string(i)+".code",code);
    }

}
double MainWindow::ZoomConvert(int value)
{
    return value/100.0;
}

void MainWindow::RadioOneChanged()
{
    //QMessageBox::information(this,"OUUUUU","ONE WAS SELECTED");
}
void MainWindow::RadioSeveralChanged()
{
    //QMessageBox::information(this,"OUUUUU","SEVERAL WAS SELECTED");
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
        designReader=std::make_shared<GDSIIDesignReader>(GDSIIDesignReader());
        designLoaded=false;
        try
        {    
            //сделать динамическую подмену имени файла источника!!
            design=designReader->MakeModel();
            if(design!=0)
            {
               designLoaded=true;

               scanner=std::make_shared<HotSpotScaner>(HotSpotScaner(design));
               QMessageBox::information(this,"Success","Design from file '"+fileInfo.baseName()+"' was successfully loaded");
               setWindowTitle("GDSIIViewer - "+fileInfo.baseName()+"."+extension+" Separate Layers: ["+QString::number(design->GetLayersSet().size())+"]");
               //design->ShowInfo();
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
    design.reset();
    designReader.reset();
    //    delete design;
//    delete designReader;

    layerForView=0;
    design=0;
    designReader=0;
}
