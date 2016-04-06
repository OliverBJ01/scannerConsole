#-------------------------------------------------
#
# Project created by QtCreator 2014-08-09T19:49:30
#
#-------------------------------------------------

QT      += core gui \
        network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTestWidget
TEMPLATE = app


SOURCES += main.cpp \
    console.cpp \
    commsScanner.cpp \
    commsOpencv.cpp \
    testRoutines.cpp \
    calibrateSystem.cpp \
    ScannerDraw.cpp


HEADERS  += \ 
    console.h \
    scannerDraw.h

FORMS    += \    
    consoleForm.ui
