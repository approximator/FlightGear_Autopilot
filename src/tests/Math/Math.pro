#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T07:56:56
#
#-------------------------------------------------

QT       += widgets declarative qml quick network svg xml testlib

TARGET = tst_math
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += tst_math.cpp \
    ../../FlightController/FgMath.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../FlightController/FgMath.h \
    tst_math.h
