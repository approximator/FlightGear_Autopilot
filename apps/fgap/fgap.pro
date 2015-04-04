include(../../autopilot.pri)

QT += widgets gui qml quick network xml svg
QTPLUGIN += qsvg

TARGET = $$FGAP_APP_TARGET
DESTDIR = $$FGAP_APP_PATH
TEMPLATE = app

target.path = $$FGAP_INSTALL_PATH
INSTALLS += target
DEFINES += INSTALL_PREFIX=$$FGAP_INSTALL_PATH

SOURCES += $$PWD/src/fgap_main.cpp \
    $$PWD/src/FgAircraft.cpp \
    $$PWD/src/FgTransport.cpp \
    $$PWD/src/FgGenericProtocol.cpp \
    $$PWD/src/FgController.cpp \
    $$PWD/src/FgAutopilot.cpp \
    $$PWD/src/FgControlledAircraft.cpp

HEADERS  += \
    $$PWD/src/FgAircraft.h \
    $$PWD/src/FgTransport.h \
    $$PWD/src/FgGenericProtocol.h \
    $$PWD/src/FgController.h \
    $$PWD/src/FgAutopilot.h \
    $$PWD/src/FgControlledAircraft.h
INCLUDEPATH = $$PWD/src

include(../../rpath.pri)

include(res/resources.pri)

# Use make deployqt instead of this. Only for Mac
#include(../../qml-libs/qml-libs-deploy.pri)

# Default rules for deployment.
include(deployment.pri)
