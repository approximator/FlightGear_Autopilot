!isEmpty(FGAP_PRI_INCLUDED):error("autopilot.pri already included")
FGAP_PRI_INCLUDED = 1

FGAP_VERSION = 0.0.3
CONFIG += c++11

isEmpty(FGAP_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    FGAP_BUILD_TREE = $$clean_path($$OUT_PWD)
    FGAP_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
    FGAP_BUILD_TREE = $$system_path($$FGAP_BUILD_TREE)
}

ROOT_DIR     = $$system_path($$PWD)
SCRIPTS_DIR  = $$system_path($$ROOT_DIR/../scripts)
CONFIGS_DIR  = $$system_path($$ROOT_DIR/../doc/config)
QML_FGEAR    = $$system_path($$ROOT_DIR/Gui/qml/qml-fgear/modules)
QML_MATERIAL = $$system_path($$ROOT_DIR/../qml-material/modules)
FGAP_SOURCE_TREE = $$system_path($$PWD)

macx {
    FGAP_APP_TARGET                 = "FlightGear Autopilot"
    FGAP_APP_PATH                   = $$FGAP_BUILD_TREE
    FGAP_BUNDLE_PATH                = $$FGAP_APP_PATH/$${FGAP_APP_TARGET}.app
    FGAP_LIBRARY_PATH               = $$FGAP_BUNDLE_PATH/Contents/PlugIns
    FGAP_DATA_PATH                  = $$FGAP_BUNDLE_PATH/Contents/Resources
    FGAP_DOC_PATH                   = $$FGAP_DATA_PATH/doc
    FGAP_BIN_PATH                   = $$FGAP_BUNDLE_PATH/Contents/MacOS
    FGAP_QML_MODULES_PATH           = $$FGAP_DATA_PATH/qml
    CONFIG_PATH = $$relative_path($$FGAP_DATA_PATH/config, $$FGAP_BIN_PATH)
    configs.path = $$relative_path($$FGAP_DATA_PATH/config, $$FGAP_BUNDLE_PATH)
    configs.files = $$files("$$CONFIGS_DIR/*")
    QMAKE_BUNDLE_DATA += configs
} else {
    FGAP_APP_TARGET                 = fgautopilot
    FGAP_INSTALL_PATH               = $$system_path($$FGAP_BUILD_TREE/$$FGAP_APP_TARGET-$$FGAP_VERSION)
    FGAP_AUX_DIR                    = $$system_path($$FGAP_INSTALL_PATH/data)
    FGAP_INSTALL_LIBRARY_PATH       = $$system_path($$FGAP_AUX_DIR/lib)
    FGAP_INSTALL_PLUGINS_DIR        = $$system_path($$FGAP_AUX_DIR/plugins)
    FGAP_INSTALL_QML_MODULES_PATH   = $$system_path($$FGAP_AUX_DIR/qml)

    configs.path = $$system_path("$$FGAP_AUX_DIR/config")
    configs.files = $$files("$$CONFIGS_DIR/*")
    INSTALLS += configs
    CONFIG_PATH = $$relative_path($$FGAP_AUX_DIR/config, $$FGAP_INSTALL_PATH)
}

qml_fgear.path  = $$FGAP_INSTALL_QML_MODULES_PATH
qml_fgear.files = $$QML_FGEAR/*
INSTALLS += qml_fgear

qml_material_modules.path = $$FGAP_INSTALL_QML_MODULES_PATH
qml_material_modules.files = $$QML_MATERIAL/*
INSTALLS += qml_material_modules

FGAP_QML_RELATIVE_PATH = $$relative_path($$FGAP_INSTALL_QML_MODULES_PATH, $$FGAP_INSTALL_PATH)
FGAP_PLUGINS_RELATIVE_PATH = $$relative_path($$FGAP_INSTALL_PLUGINS_DIR, $$FGAP_INSTALL_PATH)

DEFINES += FGAP_QML_RELATIVE_PATH=\\\"$$FGAP_QML_RELATIVE_PATH\\\"
DEFINES += FGAP_QML_MODULES_PATH=\\\"$$FGAP_QML_RELATIVE_PATH\\\"
DEFINES += FGAP_PLUGINS_PATH=\\\"$$FGAP_PLUGINS_RELATIVE_PATH\\\"
DEFINES += CONFIG_PATH=\\\"$$CONFIG_PATH\\\"

CONFIG += depend_includepath

unix {
    # enable additional warnings
    QMAKE_CXXFLAGS += -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast

    # get rid of Qt related warnings
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]" -isystem "$$[QT_INSTALL_HEADERS]/QtWidgets"
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/QtXml" -isystem "$$[QT_INSTALL_HEADERS]/QtGui"
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/QtCore"
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/QtQml"
    QMAKE_CXXFLAGS += -isystem "$$THIRD_PARTY_DIR/include"
}

defineReplace(findPython) {  # todo: add Python3
    PYTHON_EXE = python.exe
    SEPARATOR = ;
    unix:PYTHON_EXE = python
    unix:SEPARATOR = :

    PP = $$(PATH)
    pathDirs = $$split(PP, $$SEPARATOR))
    # Add some additional dirs to check for python
    pathDirs += "C:/Python34" "C:/Python27" "C:/WINDOWS/system32" "C:/WINDOWS"
    pathDirs += "C:/Program Files/Python27" "C:/Program Files/Python34"
    for (pathDir, pathDirs) {
        PYTHON_PATH = $$system_path($${pathDir}/$$PYTHON_EXE)
        # message(Looking for python in: $$PYTHON_PATH)
        exists($$PYTHON_PATH) {
            message(Python found: $$PYTHON_PATH)
            return($$PYTHON_PATH)
        }
    }
    # message(Python not found)
}