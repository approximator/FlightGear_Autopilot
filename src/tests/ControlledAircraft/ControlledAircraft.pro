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
    ../../FlightController/FgControlledAircraft.cpp \
    ../../FlightController/FgAircraft.cpp \
    ../../FlightController/FgAutopilot.cpp \
    ../../FlightController/FgFlightgear.cpp \
    ../../FlightController/FgGenericProtocol.cpp \
    ../../FlightController/FgTransport.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../FlightController/FgControlledAircraft.h \
    ../../FlightController/FgAircraft.h \
    ../../FlightController/FgAutopilot.h \
    ../../FlightController/FgFlightgear.h \
    ../../FlightController/FgGenericProtocol.h \
    ../../FlightController/FgTransport.h
