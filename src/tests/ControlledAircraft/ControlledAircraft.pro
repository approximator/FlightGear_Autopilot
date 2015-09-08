#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T07:56:56
#
#-------------------------------------------------

QT       += widgets declarative qml quick network svg xml testlib

TARGET = tst_controlledaircrafttest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += tst_controlledaircrafttest.cpp \
    ../../FlightController/vehicle/FgAircraft.cpp \
    ../../FlightController/vehicle/FgControlledAircraft.cpp \
    ../../FlightController/vehicle/FgVehicle.cpp \
    ../../FlightController/flightgear/FgFlightgear.cpp \
    ../../FlightController/flightgear/FgGenericProtocol.cpp \
    ../../FlightController/flightgear/FgTransport.cpp \
    ../../FlightController/autopilot/FgAircraftAutopilot.cpp \
    ../../FlightController/autopilot/FgAutopilot.cpp \
    ../../FlightController/utils/FgMath.cpp \
    ../../FlightController/utils/FgPid.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../FlightController/vehicle/FgAircraft.h \
    ../../FlightController/vehicle/FgControlledAircraft.h \
    ../../FlightController/vehicle/FgVehicle.h \
    ../../FlightController/flightgear/FgFlightgear.h \
    ../../FlightController/flightgear/FgGenericProtocol.h \
    ../../FlightController/flightgear/FgTransport.h \
    ../../FlightController/autopilot/FgAircraftAutopilot.h \
    ../../FlightController/autopilot/FgAutopilot.h \
    ../../FlightController/utils/FgMath.h \
    ../../FlightController/utils/FgPid.h
    tst_controlledaircrafttest.h

INCLUDEPATH += $$shell_path($$PWD/../../FlightController)
INCLUDEPATH += $$shell_path($$PWD/../../FlightController/utils)
