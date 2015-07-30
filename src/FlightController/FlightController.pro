include(../main.pri)

QT += widgets gui qml quick network xml svg
QTPLUGIN += qsvg

TARGET = $$FGAP_APP_TARGET
TEMPLATE = app

target.path = $$FGAP_INSTALL_PATH
DEFINES += INSTALL_PREFIX=$$FGAP_INSTALL_PATH
LIBS += -lglog

SOURCES += \
    $$PWD/FgPid.cpp \
    $$PWD/FgMath.cpp \
    $$ROOT_DIR/main.cpp \
    $$PWD/FgAircraft.cpp \
    $$PWD/FgTransport.cpp \
    $$PWD/FgAutopilot.cpp \
    $$PWD/FgFlightgear.cpp \
    $$PWD/FgAircraftsModel.cpp \
    $$PWD/FgGenericProtocol.cpp \
    $$PWD/FgControlledAircraft.cpp

HEADERS  += \
    $$PWD/log.h \
    $$PWD/FgPid.h \
    $$PWD/FgMath.h \
    $$PWD/FgAircraft.h \
    $$PWD/FgTransport.h \
    $$PWD/FgAutopilot.h \
    $$PWD/FgFlightgear.h \
    $$PWD/FgAircraftsModel.h \
    $$PWD/FgGenericProtocol.h \
    $$PWD/FgControlledAircraft.h

INCLUDEPATH = $$PWD

include($$FGAP_SOURCE_TREE/rpath.pri)
include($$FGAP_SOURCE_TREE/resources/resources.pri)

# Default rules for deployment.
include($$FGAP_SOURCE_TREE/deployment.pri)

