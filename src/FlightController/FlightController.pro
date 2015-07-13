include(../main.pri)

QT += widgets gui qml quick network xml svg
QTPLUGIN += qsvg

TARGET = $$FGAP_APP_TARGET
DESTDIR = $$FGAP_APP_PATH
TEMPLATE = app

target.path = $$FGAP_INSTALL_PATH
DEFINES += INSTALL_PREFIX=$$FGAP_INSTALL_PATH

configs.path = $$shell_path("$$FGAP_APP_PATH/config")
configs.files = $$files("$$CONFIGS_DIR/*.json")
INSTALLS += configs

SOURCES += $$ROOT_DIR/main.cpp \
    $$PWD/FgAircraft.cpp \
    $$PWD/FgTransport.cpp \
    $$PWD/FgGenericProtocol.cpp \
    $$PWD/FgController.cpp \
    $$PWD/FgAutopilot.cpp \
    $$PWD/FgControlledAircraft.cpp \
    $$PWD/FgFlightgear.cpp \
    ../Gui/widgets/mainwindow.cpp \
    ../Gui/widgets/aircraftslist.cpp

HEADERS  += \
    $$PWD/FgAircraft.h \
    $$PWD/FgTransport.h \
    $$PWD/FgGenericProtocol.h \
    $$PWD/FgController.h \
    $$PWD/FgAutopilot.h \
    $$PWD/FgControlledAircraft.h \
    $$PWD/FgFlightgear.h \
    ../Gui/widgets/mainwindow.h \
    ../Gui/widgets/aircraftslist.h

FORMS += \
    ../Gui/widgets/mainwindow.ui

INCLUDEPATH = $$PWD
INCLUDEPATH += $$shell_path($$absolute_path($$PWD/../Gui/widgets))

include($$FGAP_SOURCE_TREE/rpath.pri)
include($$FGAP_SOURCE_TREE/resources/resources.pri)

# Default rules for deployment.
include($$FGAP_SOURCE_TREE/deployment.pri)
