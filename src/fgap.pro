#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T09:59:06
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fgap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    FgAircraft.cpp \
    FgTransport.cpp \
    FgGenericProtocol.cpp

HEADERS  += mainwindow.h \
    FgAircraft.h \
    FgTransport.h \
    FgGenericProtocol.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
