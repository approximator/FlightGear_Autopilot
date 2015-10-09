include(main.pri)

TEMPLATE = subdirs
CONFIG  += ordered
SUBDIRS  = FlightController

DISTFILES += $$files($$SCRIPTS_DIR/*.sh) $$files($$SCRIPTS_DIR/*.py)
DISTFILES += $$files($$CONFIGS_DIR/*)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/*)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/AutopilotItems/*)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/SettingsItems/*)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/Pointers/*)
DISTFILES += $$system_path($$ROOT_DIR/../.travis.yml)

BASENAME = $$(INSTALL_BASENAME)
isEmpty(BASENAME): BASENAME = $$FGAP_APP_TARGET

PYTHON = $$findPython()
message(PYTHON: $$PYTHON)
BUILD_TYPE = Release
CONFIG(debug, debug|release) {
    BUILD_TYPE = Debug
}

macx {
    APPBUNDLE = "$$FGAP_BUNDLE_PATH"
    deployqt.commands = $$SCRIPTS_DIR/deployqtHelper_mac.sh \"$${APPBUNDLE}\" \"$$[QT_INSTALL_QML]\"
}
else {
    deployqt.commands = python -u $$shell_quote($$system_path($$SCRIPTS_DIR/deployqt.py))               \
                                    $$shell_quote($$system_path($$FGAP_INSTALL_PATH/$$FGAP_APP_TARGET)) \
                                    $$shell_quote($$FGAP_INSTALL_PATH)         \
                                    $$shell_quote($$FGAP_AUX_DIR)              \
                                    $$shell_quote($$FGAP_INSTALL_LIBRARY_PATH) \
                                    $$shell_quote($$system_path($(QMAKE)))     \
                                    $$BUILD_TYPE
    deployqt.depends = install
}

deploy_ext_qml.depends = install
deploy_all.depends = deployqt

QMAKE_EXTRA_TARGETS += deployqt deploy_all

