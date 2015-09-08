#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T07:56:56
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_math
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += tst_math.cpp \
    ../../FlightController/utils/FgMath.cpp


DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tst_math.h \
    ../../FlightController/utils/FgMath.h
