include(../main.pri)

QT += widgets gui qml quick network xml svg
QTPLUGIN += qsvg

TARGET = $$FGAP_APP_TARGET
DESTDIR = $$FGAP_APP_PATH
TEMPLATE = app

target.path = $$FGAP_INSTALL_PATH
DEFINES += INSTALL_PREFIX=$$FGAP_INSTALL_PATH

# define path to config files
macx {

CONFIG_PATH = $$relative_path($$FGAP_DATA_PATH/config, $$FGAP_BIN_PATH)
configs.path = $$relative_path($$FGAP_DATA_PATH/config, $$FGAP_BUNDLE_PATH)
configs.files = $$files("$$CONFIGS_DIR/*.json")
QMAKE_BUNDLE_DATA += configs

} else {

CONFIG_PATH = $$relative_path($$FGAP_BIN_PATH/config, $$FGAP_BIN_PATH)
configs.path = $$shell_path("$$FGAP_BIN_PATH/config")
configs.files = $$files("$$CONFIGS_DIR/*.json")
INSTALLS += configs

}

DEFINES += CONFIG_PATH=\\\"$$CONFIG_PATH\\\"

SOURCES += $$ROOT_DIR/main.cpp \
    $$PWD/FgAircraft.cpp \
    $$PWD/FgTransport.cpp \
    $$PWD/FgGenericProtocol.cpp \
    $$PWD/FgController.cpp \
    $$PWD/FgAutopilot.cpp \
    $$PWD/FgControlledAircraft.cpp \
    $$PWD/FgFlightgear.cpp \
    $$PWD/FgPid.cpp \
    $$PWD/FgMath.cpp \
    $$ROOT_DIR/Gui/widgets/mainwindow.cpp \
    $$ROOT_DIR/Gui/widgets/aircraftslist.cpp \
    $$ROOT_DIR/Gui/widgets/autopilotwidget.cpp \
    $$ROOT_DIR/Gui/widgets/pictorialindicatorwidget.cpp

HEADERS  += \
    $$PWD/FgAircraft.h \
    $$PWD/FgTransport.h \
    $$PWD/FgGenericProtocol.h \
    $$PWD/FgController.h \
    $$PWD/FgAutopilot.h \
    $$PWD/FgControlledAircraft.h \
    $$PWD/FgFlightgear.h \
    $$PWD/FgPid.h \
    $$PWD/FgMath.h \
    $$ROOT_DIR/Gui/widgets/mainwindow.h \
    $$ROOT_DIR/Gui/widgets/aircraftslist.h \
    $$ROOT_DIR/Gui/widgets/autopilotwidget.h \
    $$ROOT_DIR/Gui/widgets/pictorialindicatorwidget.h

FORMS += \
    $$ROOT_DIR/Gui/widgets/mainwindow.ui

INCLUDEPATH = $$PWD
INCLUDEPATH += $$shell_path($$ROOT_DIR/Gui/widgets)

include($$FGAP_SOURCE_TREE/rpath.pri)
include($$FGAP_SOURCE_TREE/resources/resources.pri)

# Default rules for deployment.
include($$FGAP_SOURCE_TREE/deployment.pri)
