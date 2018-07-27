/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QWidget *centralWidget;
    QScrollBar *verticalScrollBar;
    QScrollBar *horizontalScrollBar;
    QLabel *labZoom;
    QSpinBox *spbZoom;
    QLabel *labLayer;
    QSpinBox *spbLayer;
    QPushButton *btnOK;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vertLayout;
    QGroupBox *groupBox;
    QRadioButton *rbOne;
    QRadioButton *rbSeveral;
    QPushButton *btnScann;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(758, 428);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalScrollBar = new QScrollBar(centralWidget);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(630, 20, 16, 341));
        verticalScrollBar->setOrientation(Qt::Vertical);
        horizontalScrollBar = new QScrollBar(centralWidget);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(10, 360, 621, 20));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        labZoom = new QLabel(centralWidget);
        labZoom->setObjectName(QStringLiteral("labZoom"));
        labZoom->setGeometry(QRect(660, 10, 31, 16));
        spbZoom = new QSpinBox(centralWidget);
        spbZoom->setObjectName(QStringLiteral("spbZoom"));
        spbZoom->setGeometry(QRect(700, 10, 42, 22));
        labLayer = new QLabel(centralWidget);
        labLayer->setObjectName(QStringLiteral("labLayer"));
        labLayer->setGeometry(QRect(660, 50, 31, 16));
        spbLayer = new QSpinBox(centralWidget);
        spbLayer->setObjectName(QStringLiteral("spbLayer"));
        spbLayer->setGeometry(QRect(700, 50, 42, 22));
        btnOK = new QPushButton(centralWidget);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(670, 90, 75, 23));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 621, 341));
        vertLayout = new QVBoxLayout(verticalLayoutWidget);
        vertLayout->setSpacing(6);
        vertLayout->setContentsMargins(11, 11, 11, 11);
        vertLayout->setObjectName(QStringLiteral("vertLayout"));
        vertLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(650, 120, 101, 61));
        rbOne = new QRadioButton(groupBox);
        rbOne->setObjectName(QStringLiteral("rbOne"));
        rbOne->setGeometry(QRect(10, 20, 101, 17));
        rbSeveral = new QRadioButton(groupBox);
        rbSeveral->setObjectName(QStringLiteral("rbSeveral"));
        rbSeveral->setGeometry(QRect(10, 40, 101, 21));
        btnScann = new QPushButton(centralWidget);
        btnScann->setObjectName(QStringLiteral("btnScann"));
        btnScann->setGeometry(QRect(640, 190, 111, 51));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 758, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "GDSIIViewer", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        labZoom->setText(QApplication::translate("MainWindow", "Zoom", nullptr));
        labLayer->setText(QApplication::translate("MainWindow", "Layer", nullptr));
        btnOK->setText(QApplication::translate("MainWindow", "OK", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Layer display mode", nullptr));
        rbOne->setText(QApplication::translate("MainWindow", "One", nullptr));
        rbSeveral->setText(QApplication::translate("MainWindow", "Several", nullptr));
        btnScann->setText(QApplication::translate("MainWindow", "Extract hot spots", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
