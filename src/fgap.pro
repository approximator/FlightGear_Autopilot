#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T09:59:06
#
#-------------------------------------------------
include(fgap.pri)

QT       += core gui qml quick
QT += network

TARGET = $$FGAP_APP_TARGET
DESTDIR = $$FGAP_APP_PATH
TEMPLATE = app


SOURCES += main.cpp\
    FgAircraft.cpp \
    FgTransport.cpp \
    FgGenericProtocol.cpp \
    FgController.cpp \
    FgAutopilot.cpp \
    FgControlledAircraft.cpp

HEADERS  += \
    FgAircraft.h \
    FgTransport.h \
    FgGenericProtocol.h \
    FgController.h \
    FgAutopilot.h \
    FgControlledAircraft.h

# Additional import path used to resolve QML modules in Qt Creator's code model
# EXTERNAL_MODULES_PATH - path to external qml sources.
# If it is empty, needed modules will be search in default $$[QT_INSTALL_QML] path.
EXTERNAL_MODULES_PATH = /Users/andrey/Project/GitHub

include(qml-modules-import.pri)

include(res/resources.pri)

# Default rules for deployment.
include(deployment.pri)