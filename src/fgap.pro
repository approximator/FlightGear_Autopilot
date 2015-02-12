#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T09:59:06
#
#-------------------------------------------------

QT       += core gui qml quick
QT += network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fgap
TEMPLATE = app


SOURCES += main.cpp\
    FgAircraft.cpp \
    FgTransport.cpp \
    FgGenericProtocol.cpp \
    FgController.cpp

HEADERS  += \
    FgAircraft.h \
    FgTransport.h \
    FgGenericProtocol.h \
    FgController.h

FORMS    +=

include(res/resources.pri)
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
