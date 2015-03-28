include(../../autopilot.pri)

QT += widgets gui qml quick network
TARGET = $$FGAP_APP_TARGET
DESTDIR = $$FGAP_APP_PATH
TEMPLATE = app

#Check it
#target.path = $(PREFIX)
#INSTALLS += target
#DEFINES += INSTALL_PREFIX=$(PREFIX)

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

include(res/resources.pri)

include(../../qml-libs/qml-libs-deploy.pri)

# Default rules for deployment.
include(deployment.pri)
