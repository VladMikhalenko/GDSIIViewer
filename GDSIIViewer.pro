#-------------------------------------------------
#
# Project created by QtCreator 2018-07-27T14:59:21
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = GDSIIViewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += no_keywords
SOURCES += \
    HotSpotScaner.cpp \
    main.cpp \
    mainwindow.cpp \
    src/DataReader/BinDataTypeReader.cpp \
    src/DataReader/GDSIIDesignReader.cpp \
    src/DataReader/RecordSupplier.cpp \
    src/DataSource/GDSIIBinSource.cpp \
    src/DataSource/GDSIISourceConsole.cpp \
    src/DataSource/GDSIISourceTXT.cpp \
    src/DataSource/SourceFactory.cpp \
    src/GDSIIGeometry/Primitives/GDSIILine.cpp \
    src/GDSIIGeometry/Primitives/GDSIIPoint.cpp \
    src/GDSIIModel/GDSIIDesign/GDSIIDesign.cpp \
    src/GDSIIModel/GDSIIElements/AREF.cpp \
    src/GDSIIModel/GDSIIElements/Boundary.cpp \
    src/GDSIIModel/GDSIIElements/Box.cpp \
    src/GDSIIModel/GDSIIElements/GDSIIElement.cpp \
    src/GDSIIModel/GDSIIElements/Node.cpp \
    src/GDSIIModel/GDSIIElements/Path.cpp \
    src/GDSIIModel/GDSIIElements/SREF.cpp \
    src/GDSIIModel/GDSIIElements/Text.cpp \
    src/GDSIIModel/GDSIIRecords/GDSIIRecord.cpp \
    src/GDSIIModel/GDSIIRecords/Record00_Header.cpp \
    src/GDSIIModel/GDSIIRecords/record01_bgnlib.cpp \
    src/GDSIIModel/GDSIIRecords/record02_libname.cpp \
    src/GDSIIModel/GDSIIRecords/Record03_Units.cpp \
    src/GDSIIModel/GDSIIRecords/record04_endlib.cpp \
    src/GDSIIModel/GDSIIRecords/Record05_Bgnstr.cpp \
    src/GDSIIModel/GDSIIRecords/record06_strname.cpp \
    src/GDSIIModel/GDSIIRecords/Record07_Endstr.cpp \
    src/GDSIIModel/GDSIIRecords/record08_boundary.cpp \
    src/GDSIIModel/GDSIIRecords/Record09_Path.cpp \
    src/GDSIIModel/GDSIIRecords/record10_sref.cpp \
    src/GDSIIModel/GDSIIRecords/Record11_Aref.cpp \
    src/GDSIIModel/GDSIIRecords/record12_text.cpp \
    src/GDSIIModel/GDSIIRecords/Record13_Layer.cpp \
    src/GDSIIModel/GDSIIRecords/record14_datatype.cpp \
    src/GDSIIModel/GDSIIRecords/Record15_Width.cpp \
    src/GDSIIModel/GDSIIRecords/Record16_XY.cpp \
    src/GDSIIModel/GDSIIRecords/Record17_Endel.cpp \
    src/GDSIIModel/GDSIIRecords/record18_sname.cpp \
    src/GDSIIModel/GDSIIRecords/Record19_Colrow.cpp \
    src/GDSIIModel/GDSIIRecords/record20_textnode.cpp \
    src/GDSIIModel/GDSIIRecords/Record21_Node.cpp \
    src/GDSIIModel/GDSIIRecords/record22_texttype.cpp \
    src/GDSIIModel/GDSIIRecords/Record23_Presentation.cpp \
    src/GDSIIModel/GDSIIRecords/record24_spacing.cpp \
    src/GDSIIModel/GDSIIRecords/Record25_String.cpp \
    src/GDSIIModel/GDSIIRecords/record26_strans.cpp \
    src/GDSIIModel/GDSIIRecords/Record27_Mag.cpp \
    src/GDSIIModel/GDSIIRecords/record28_angle.cpp \
    src/GDSIIModel/GDSIIRecords/Record31_Reflibs.cpp \
    src/GDSIIModel/GDSIIRecords/record32_fonts.cpp \
    src/GDSIIModel/GDSIIRecords/Record33_Pathtype.cpp \
    src/GDSIIModel/GDSIIRecords/record34_generations.cpp \
    src/GDSIIModel/GDSIIRecords/Record35_Attrtable.cpp \
    src/GDSIIModel/GDSIIRecords/record36_styptable.cpp \
    src/GDSIIModel/GDSIIRecords/Record37_Strtype.cpp \
    src/GDSIIModel/GDSIIRecords/record38_elflags.cpp \
    src/GDSIIModel/GDSIIRecords/Record39_Elkey.cpp \
    src/GDSIIModel/GDSIIRecords/record40_linktype.cpp \
    src/GDSIIModel/GDSIIRecords/Record41_Linkeys.cpp \
    src/GDSIIModel/GDSIIRecords/record42_nodetype.cpp \
    src/GDSIIModel/GDSIIRecords/Record43_Propattr.cpp \
    src/GDSIIModel/GDSIIRecords/record44_propvalue.cpp \
    src/GDSIIModel/GDSIIRecords/Record45_Box.cpp \
    src/GDSIIModel/GDSIIRecords/record46_boxtype.cpp \
    src/GDSIIModel/GDSIIRecords/Record47_Plex.cpp \
    src/GDSIIModel/GDSIIRecords/record48_bgnextn.cpp \
    src/GDSIIModel/GDSIIRecords/Record49_Endextn.cpp \
    src/GDSIIModel/GDSIIRecords/record50_tapenum.cpp \
    src/GDSIIModel/GDSIIRecords/Record51_Tapecode.cpp \
    src/GDSIIModel/GDSIIRecords/record52_strclass.cpp \
    src/GDSIIModel/GDSIIRecords/Record53_Reserved.cpp \
    src/GDSIIModel/GDSIIRecords/record54_format.cpp \
    src/GDSIIModel/GDSIIRecords/Record55_Mask.cpp \
    src/GDSIIModel/GDSIIRecords/record56_endmasks.cpp \
    src/GDSIIModel/GDSIIRecords/Record57_Libdirsize.cpp \
    src/GDSIIModel/GDSIIRecords/record58_srfname.cpp \
    src/GDSIIModel/GDSIIRecords/Record59_Libsecur.cpp \
    src/GDSIIModel/GDSIIStructure/Structure.cpp \
    src/Global/AnError.cpp \
    src/Global/GlobalOptions.cpp \
    src/GUI/DrawingArea.cpp \
    src/GUI/GDSIILineContainer.cpp \
    src/GUI/GUIClient.cpp \
    src/GUI/LayerForView.cpp \
    src/Interfaces/UI/IGDSIIPainter.cpp \
    src/LithographyTools/GaussianKernel.cpp \
    src/LithographyTools/IntensityField.cpp \
    src/LithographyTools/LineAnalyzer.cpp \
    src/LithographyTools/LithographicRay.cpp \
    src/MathTools/FunctionProvider.cpp \
    utils/Convert/GDSIIConverter.cpp \
    utils/Encoder/GDSIIDesignEncoder.cpp \
    utils/Encoder/GDSIIEncoder.cpp \
    utils/FileWriter/FileWriter.cpp \
    utils/GDSIIPainter/GDSIIImageBuilder.cpp \
    src/LithographyTools/GaussianProcessor.cpp \
    utils/Encoder/PostEncodeAnalyzer.cpp \
    utils/Python/PythonHelper/PythonHelper.cpp \
    utils/Python/PythonHelper/NumpyArray.cpp \
    utils/Python/PythonHelper/PythonModule.cpp \
    utils/Python/PythonHelper/PythonMethod.cpp

HEADERS += \
    HotSpotScaner.h \
    mainwindow.h \
    inc/DataReader/BinDataTypeReader.h \
    inc/DataReader/GDSIIDesignReader.h \
    inc/DataReader/RecordSupplier.h \
    inc/DataSource/GDSIIBinSource.h \
    inc/DataSource/GDSIISourceConsole.h \
    inc/DataSource/GDSIISourceTXT.h \
    inc/DataSource/IGDSIISource.h \
    inc/DataSource/SourceFactory.h \
    inc/GDSIIGeometry/Primitives/GDSIILine.h \
    inc/GDSIIGeometry/Primitives/GDSIIPoint.h \
    inc/GDSIIModel/GDSIIDesign/GDSIIDesign.h \
    inc/GDSIIModel/GDSIIElements/AREF.h \
    inc/GDSIIModel/GDSIIElements/Boundary.h \
    inc/GDSIIModel/GDSIIElements/Box.h \
    inc/GDSIIModel/GDSIIElements/GDSIIElement.h \
    inc/GDSIIModel/GDSIIElements/Node.h \
    inc/GDSIIModel/GDSIIElements/Path.h \
    inc/GDSIIModel/GDSIIElements/SREF.h \
    inc/GDSIIModel/GDSIIElements/Text.h \
    inc/GDSIIModel/GDSIIRecords/GDSIIRecord.h \
    inc/GDSIIModel/GDSIIRecords/Record00_Header.h \
    inc/GDSIIModel/GDSIIRecords/record01_bgnlib.h \
    inc/GDSIIModel/GDSIIRecords/record02_libname.h \
    inc/GDSIIModel/GDSIIRecords/Record03_Units.h \
    inc/GDSIIModel/GDSIIRecords/record04_endlib.h \
    inc/GDSIIModel/GDSIIRecords/Record05_Bgnstr.h \
    inc/GDSIIModel/GDSIIRecords/record06_strname.h \
    inc/GDSIIModel/GDSIIRecords/Record07_Endstr.h \
    inc/GDSIIModel/GDSIIRecords/record08_boundary.h \
    inc/GDSIIModel/GDSIIRecords/Record09_Path.h \
    inc/GDSIIModel/GDSIIRecords/record10_sref.h \
    inc/GDSIIModel/GDSIIRecords/Record11_Aref.h \
    inc/GDSIIModel/GDSIIRecords/record12_text.h \
    inc/GDSIIModel/GDSIIRecords/Record13_Layer.h \
    inc/GDSIIModel/GDSIIRecords/record14_datatype.h \
    inc/GDSIIModel/GDSIIRecords/Record15_Width.h \
    inc/GDSIIModel/GDSIIRecords/Record16_XY.h \
    inc/GDSIIModel/GDSIIRecords/Record17_Endel.h \
    inc/GDSIIModel/GDSIIRecords/record18_sname.h \
    inc/GDSIIModel/GDSIIRecords/Record19_Colrow.h \
    inc/GDSIIModel/GDSIIRecords/record20_textnode.h \
    inc/GDSIIModel/GDSIIRecords/Record21_Node.h \
    inc/GDSIIModel/GDSIIRecords/record22_texttype.h \
    inc/GDSIIModel/GDSIIRecords/Record23_Presentation.h \
    inc/GDSIIModel/GDSIIRecords/record24_spacing.h \
    inc/GDSIIModel/GDSIIRecords/Record25_String.h \
    inc/GDSIIModel/GDSIIRecords/record26_strans.h \
    inc/GDSIIModel/GDSIIRecords/Record27_Mag.h \
    inc/GDSIIModel/GDSIIRecords/record28_angle.h \
    inc/GDSIIModel/GDSIIRecords/Record31_Reflibs.h \
    inc/GDSIIModel/GDSIIRecords/record32_fonts.h \
    inc/GDSIIModel/GDSIIRecords/Record33_Pathtype.h \
    inc/GDSIIModel/GDSIIRecords/record34_generations.h \
    inc/GDSIIModel/GDSIIRecords/Record35_Attrtable.h \
    inc/GDSIIModel/GDSIIRecords/record36_styptable.h \
    inc/GDSIIModel/GDSIIRecords/Record37_Strtype.h \
    inc/GDSIIModel/GDSIIRecords/record38_elflags.h \
    inc/GDSIIModel/GDSIIRecords/Record39_Elkey.h \
    inc/GDSIIModel/GDSIIRecords/record40_linktype.h \
    inc/GDSIIModel/GDSIIRecords/Record41_Linkeys.h \
    inc/GDSIIModel/GDSIIRecords/record42_nodetype.h \
    inc/GDSIIModel/GDSIIRecords/Record43_Propattr.h \
    inc/GDSIIModel/GDSIIRecords/record44_propvalue.h \
    inc/GDSIIModel/GDSIIRecords/Record45_Box.h \
    inc/GDSIIModel/GDSIIRecords/record46_boxtype.h \
    inc/GDSIIModel/GDSIIRecords/Record47_Plex.h \
    inc/GDSIIModel/GDSIIRecords/record48_bgnextn.h \
    inc/GDSIIModel/GDSIIRecords/Record49_Endextn.h \
    inc/GDSIIModel/GDSIIRecords/record50_tapenum.h \
    inc/GDSIIModel/GDSIIRecords/Record51_Tapecode.h \
    inc/GDSIIModel/GDSIIRecords/record52_strclass.h \
    inc/GDSIIModel/GDSIIRecords/Record53_Reserved.h \
    inc/GDSIIModel/GDSIIRecords/record54_format.h \
    inc/GDSIIModel/GDSIIRecords/Record55_Mask.h \
    inc/GDSIIModel/GDSIIRecords/record56_endmasks.h \
    inc/GDSIIModel/GDSIIRecords/Record57_Libdirsize.h \
    inc/GDSIIModel/GDSIIRecords/record58_srfname.h \
    inc/GDSIIModel/GDSIIRecords/Record59_Libsecur.h \
    inc/GDSIIModel/GDSIIStructure/Structure.h \
    inc/Global/AnError.h \
    inc/Global/GlobalOptions.h \
    inc/GUI/DrawingArea.h \
    inc/GUI/GDSIILineContainer.h \
    inc/GUI/GUIClient.h \
    inc/GUI/LayerForView.h \
    inc/Interfaces/UI/IGDSIIPainter.h \
    inc/LithographyTools/GaussianKernel.h \
    inc/LithographyTools/IntensityField.h \
    inc/LithographyTools/LineAnalyzer.h \
    inc/LithographyTools/LithographicRay.h \
    inc/MathTools/FunctionProvider.h \
    src/ACL.h \
    src/Point.h \
    utils/Convert/GDSIIConverter.h \
    utils/Encoder/GDSIIDesignEncoder.h \
    utils/Encoder/GDSIIEncoder.h \
    utils/FileWriter/FileWriter.h \
    utils/GDSIIPainter/GDSIIImageBuilder.h \
    inc/LithographyTools/GaussianProcessor.h \
    utils/Encoder/PostEncodeAnalyzer.h \
    utils/Python/PythonHelper/PythonHelper.h \
    utils/Python/PythonHelper/NumpyArray.h \
    utils/Python/PythonHelper/PythonModule.h \
    utils/Python/PythonHelper/PythonMethod.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    GDSIIViewer.pro

#DISTFILES +=

win32: LIBS += -LC:/Python/Anaconda3/libs/ -lpython37

INCLUDEPATH += C:/Python/Anaconda3/include
DEPENDPATH += C:/Python/Anaconda3/include

win32:!win32-g++: PRE_TARGETDEPS += C:/Python/Anaconda3/libs/python37.lib
else:win32-g++: PRE_TARGETDEPS += C:/Python/Anaconda3/libs/libpython37.a
