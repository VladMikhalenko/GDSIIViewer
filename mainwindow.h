#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "inc/GUI/DrawingArea.h"
#include "inc/GDSIIModel/GDSIIDesign/GDSIIDesign.h"
#include "inc/DataReader/GDSIIDesignReader.h"
#include "inc/GUI/LayerForView.h"
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

    std::unique_ptr<DrawingArea> dArea;

    std::shared_ptr<HotSpotScaner> scanner;

    std::shared_ptr<LayerForView> layerForView;
    std::shared_ptr<GDSIIDesign> design;
    std::shared_ptr<GDSIIDesignReader> designReader;

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

    int extractionLayer;
    int markerLayer;
	
	void paintEvent(QPaintEvent *event);
    void SetProjectWidth(int width);
    void SetProjectHeight(int height);
    double ZoomConvert(int value);

    void GetNewLayerFromDesign();
    void PrepareLineContainerForDrawing();
    void CalculateWindowToProjectCoef();

    void ResetWindowBorders();
    void ClearDataBeforeLoading();
Q_SIGNALS:
    void ZoomValueUpdated(double);

private Q_SLOTS:
    void CalculateScrolls(int value);
    void CalculateWindowPoints(double value);
    void ZoomValueChanged(int value);
    void LayerValueChanged(int value);
    void extractionLayerChanged(int value);
    void markerLayerChanged(int value);

    void BtnOkClick();
    void BtnScannClick();
    void btnEncodeClick();

    void HorizontalScrollChanged(int value);
    void VerticalScrollChanged(int value);

    void RadioOneChanged();
    void RadioSeveralChanged();

    void on_actionOpen_triggered();
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
