include(../main.pri)

QT += qml quick network xml svg
QTPLUGIN += qsvg

TARGET = $$FGAP_APP_TARGET
DESTDIR = $$FGAP_INSTALL_PATH
TEMPLATE = app

target.path = $$FGAP_BUILD_TREE
DEFINES += INSTALL_PREFIX=$$FGAP_INSTALL_PATH

SOURCES += \
    $$ROOT_DIR/main.cpp \
    $$PWD/utils/FgPid.cpp \
    $$PWD/utils/FgMath.cpp \
    $$PWD/FgAircraftsModel.cpp \
    $$PWD/vehicle/FgVehicle.cpp \
    $$PWD/vehicle/FgAircraft.cpp \
    $$PWD/autopilot/FgAutopilot.cpp \
    $$PWD/flightgear/FgTransport.cpp \
    $$PWD/flightgear/FgFlightgear.cpp \
    $$PWD/vehicle/FgControlledAircraft.cpp \
    $$PWD/flightgear/FgGenericProtocol.cpp \
    $$PWD/autopilot/FgAircraftAutopilot.cpp

HEADERS  += \
    $$PWD/utils/log.h \
    $$PWD/utils/FgPid.h \
    $$PWD/utils/FgMath.h \
    $$PWD/utils/Filesystem.h \
    $$PWD/FgAircraftsModel.h \
    $$PWD/vehicle/FgVehicle.h \
    $$PWD/vehicle/FgAircraft.h \
    $$PWD/autopilot/FgAutopilot.h \
    $$PWD/flightgear/FgTransport.h \
    $$PWD/flightgear/FgFlightgear.h \
    $$PWD/vehicle/FgControlledAircraft.h \
    $$PWD/flightgear/FgGenericProtocol.h \
    $$PWD/autopilot/FgAircraftAutopilot.h

INCLUDEPATH += $$system_path($$PWD)
INCLUDEPATH += $$system_path($$PWD/utils)

include($$FGAP_SOURCE_TREE/resources/resources.pri)
# Default rules for deployment.
include($$FGAP_SOURCE_TREE/deployment.pri)

