!isEmpty(FGAP_PRI_INCLUDED):error("autopilot.pri already included")
FGAP_PRI_INCLUDED = 1

FILIGHTGEARAUTOPILOT_VERSION = 0.0.3
CONFIG += c++11

unix {
    # enable additional warnings
    QMAKE_CXXFLAGS += -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast

    # get rid of Qt related warnings
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]" -isystem "$$[QT_INSTALL_HEADERS]/QtWidgets"
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/QtXml" -isystem "$$[QT_INSTALL_HEADERS]/QtGui"
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/QtCore"
}

isEmpty(FGAP_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    FGAP_BUILD_TREE = $$clean_path($$OUT_PWD)
    FGAP_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

ROOT_DIR = $$PWD
SCRIPTS_DIR = $$shell_path($$absolute_path(../scripts))
CONFIGS_DIR = $$shell_path($$absolute_path($$ROOT_DIR/../doc/config/))
FGAP_SOURCE_TREE = $$PWD
FGAP_APP_PATH = $$FGAP_BUILD_TREE/bin

macx {
    FGAP_APP_TARGET     = "FlightGear Autopilot"
    FGAP_BUNDLE_PATH    = $$FGAP_APP_PATH/$${FGAP_APP_TARGET}.app
    FGAP_LIBRARY_PATH   = $$FGAP_BUNDLE_PATH/Contents/PlugIns
    FGAP_DATA_PATH        = $$FGAP_BUNDLE_PATH/Contents/Resources
    FGAP_DOC_PATH         = $$FGAP_DATA_PATH/doc
    FGAP_BIN_PATH           = $$FGAP_BUNDLE_PATH/Contents/MacOS
    FGAP_QML_MODULES_PATH = $$FGAP_DATA_PATH/qml
} else {
    FGAP_APP_TARGET     = fgautopilot
    FGAP_LIBRARY_PATH   = $$FGAP_BUILD_TREE/lib
    FGAP_INSTALL_PATH   = $$FGAP_BUILD_TREE
    FGAP_DATA_PATH        = $$FGAP_BUILD_TREE/share
    FGAP_DOC_PATH         = $$FGAP_BUILD_TREE/share/doc
    FGAP_BIN_PATH         = $$FGAP_APP_PATH
    FGAP_QML_MODULES_PATH = $$FGAP_BIN_PATH/qml
}

CONFIG += depend_includepath

unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/obj/debug-shared
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/obj/release-shared

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/moc/debug-shared
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/moc/release-shared

    RCC_DIR = $${OUT_PWD}/rcc
    UI_DIR = $${OUT_PWD}/uic
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
        PYTHON_PATH = $$shell_path($${pathDir}/$$PYTHON_EXE)
        exists($$PYTHON_PATH) {
            message(Python found: $$PYTHON_PATH)
            return($$PYTHON_PATH)
        }
    }
    message(Python not found)
}
