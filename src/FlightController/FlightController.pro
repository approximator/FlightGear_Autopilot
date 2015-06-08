include(../main.pri)

QT += widgets gui qml quick network xml svg
QTPLUGIN += qsvg

TARGET = $$FGAP_APP_TARGET
DESTDIR = $$FGAP_APP_PATH
TEMPLATE = app

target.path = $$FGAP_INSTALL_PATH
INSTALLS += target
DEFINES += INSTALL_PREFIX=$$FGAP_INSTALL_PATH

SOURCES += $$ROOT_DIR/main.cpp \
    $$PWD/FgAircraft.cpp \
    $$PWD/FgTransport.cpp \
    $$PWD/FgGenericProtocol.cpp \
    $$PWD/FgController.cpp \
    $$PWD/FgAutopilot.cpp \
    $$PWD/FgControlledAircraft.cpp \
    $$PWD/FgFlightgear.cpp

HEADERS  += \
    $$PWD/FgAircraft.h \
    $$PWD/FgTransport.h \
    $$PWD/FgGenericProtocol.h \
    $$PWD/FgController.h \
    $$PWD/FgAutopilot.h \
    $$PWD/FgControlledAircraft.h \
    $$PWD/FgFlightgear.h
INCLUDEPATH = $$PWD

include($$FGAP_SOURCE_TREE/rpath.pri)
include($$FGAP_SOURCE_TREE/resources/resources.pri)

# Default rules for deployment.
include($$FGAP_SOURCE_TREE/deployment.pri)
