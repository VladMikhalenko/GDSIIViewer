#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "DrawingArea.h"
#include "src/GDSIIDesign.h"
#include "src/GDSIIDesignReader.h"
#include "src/LayerForView.h"
#include "HotSpotScaner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    
private:
    Ui::MainWindow *ui;
    DrawingArea* dArea;

    HotSpotScaner* scanner;

    LayerForView* layerForView;
    GDSIIDesign* design;
    GDSIIDesignReader* designReader;

    bool designLoaded;


    double zoomCoef;
    double winProjCoef;
    int currentLayer;

    int horScrollValue;
    int verScrollValue;

    double winMinX;
    double winMaxX;
    double winMinY;
    double winMaxY;

    int ProjectWidth;
    int ProjectHeight;

	
	void paintEvent(QPaintEvent *event);
    void SetProjectWidth(int width);
    void SetProjectHeight(int height);
    double ZoomConvert(int value);

    void GetNewLayerFromDesign();
    void PrepareLineContainerForDrawing();
    void CalculateWindowToProjectCoef();

    void ResetWindowBorders();
    void ClearDataBeforeLoading();
signals:
    void ZoomValueUpdated(double);

private slots:
    void CalculateScrolls(int value);
    void CalculateWindowPoints(double value);
    void ZoomValueChanged(int value);
    void LayerValueChanged(int value);

    void BtnOkClick();
    void BtnScannClick();

    void HorizontalScrollChanged(int value);
    void VerticalScrollChanged(int value);

    void RadioOneChanged();
    void RadioSeveralChanged();

    void on_actionOpen_triggered();
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
