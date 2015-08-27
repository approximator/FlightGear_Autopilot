include(main.pri)

TEMPLATE = subdirs
CONFIG  += ordered
SUBDIRS  = FlightController

DISTFILES += $$files($$SCRIPTS_DIR/*.sh) $$files($$SCRIPTS_DIR/*.py)
DISTFILES += $$files($$CONFIGS_DIR/*)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/*.qml)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/AutopilotItems/*.qml)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/Pointers/*.qml)
DISTFILES += $$ROOT_DIR/../.travis.yml

BASENAME = $$(INSTALL_BASENAME)
isEmpty(BASENAME): BASENAME = $$FGAP_APP_TARGET

PYTHON = $$findPython()
BUILD_TYPE = Release
CONFIG(debug, debug|release) {
    BUILD_TYPE = Debug
}

macx {
    APPBUNDLE = "$$FGAP_BUNDLE_PATH"
    deployqt.commands = $$SCRIPTS_DIR/deployqtHelper_mac.sh \"$${APPBUNDLE}\" \"$$[QT_INSTALL_QML]\"
}
else {
    deployqt.commands = $$PYTHON -u $$shell_path(\"$$SCRIPTS_DIR/deployqt.py\")             \
                                    $$shell_path(\"$$FGAP_INSTALL_PATH/$$FGAP_APP_TARGET\") \
                                    $$FGAP_INSTALL_PATH         \
                                    $$FGAP_AUX_DIR              \
                                    $$FGAP_INSTALL_LIBRARY_PATH \
                                    $$shell_path(\"$(QMAKE)\")  \
                                    \"$$BUILD_TYPE\"
    deployqt.depends = install
}

deploy_ext_qml.commands = $$PYTHON -u $$shell_path(\"$$SCRIPTS_DIR/load_qml_modules.py\") \
                                      \"$$FGAP_INSTALL_QML_MODULES_PATH\"
deploy_ext_qml.depends = install
deploy_all.depends = deployqt deploy_ext_qml

QMAKE_EXTRA_TARGETS += deployqt deploy_ext_qml deploy_all

