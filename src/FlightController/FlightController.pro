include(../main.pri)

QT += widgets gui qml quick network xml svg
QTPLUGIN += qsvg

TARGET = $$FGAP_APP_TARGET
DESTDIR = $$FGAP_APP_PATH
TEMPLATE = app

target.path = $$FGAP_INSTALL_PATH
DEFINES += INSTALL_PREFIX=$$FGAP_INSTALL_PATH
LIBS += -lglog

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
