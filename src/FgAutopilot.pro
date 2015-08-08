include(main.pri)

TEMPLATE = subdirs
CONFIG   += ordered
SUBDIRS  = FlightController

DISTFILES += $$files($$SCRIPTS_DIR/*.sh) $$files($$SCRIPTS_DIR/*.py)
DISTFILES += $$files($$CONFIGS_DIR/*.json)
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
    deployqt.commands = $$PYTHON -u $$shell_path(\"$$SCRIPTS_DIR/deployqt.py\") \
                                    $$FGAP_AUX_DIR $$shell_path(\"$(QMAKE)\") \
                                    \"$$BUILD_TYPE\"
    deployqt.depends = install


QT_CONFIG_CONTENT = [Paths] \
        Libraries=$$relative_path($$FGAP_INSTALL_LIBRARY_PATH, $$FGAP_INSTALL_PATH) \
        Plugins=$$relative_path($$FGAP_AUX_DIR/plugins, $$FGAP_INSTALL_PATH) \
        Imports=$$relative_path($$FGAP_AUX_DIR/imports, $$FGAP_INSTALL_PATH) \
        Qml2Imports=$$relative_path($$FGAP_AUX_DIR/qml, $$FGAP_INSTALL_PATH)
       write_file($$FGAP_INSTALL_PATH/qt.conf, QT_CONFIG_CONTENT)
}


deploy_ext_qml.commands = $$PYTHON -u $$shell_path(\"$$SCRIPTS_DIR/load_qml_modules.py\") \
                                      $$shell_path(\"$$ROOT_DIR/Gui/qml\") \
                                      \"$$FGAP_INSTALL_QML_MODULES_PATH\"
deploy_ext_qml.depends = deployqt

deploy_all.depends = deploy_ext_qml

INSTALLER_ARCHIVE_FROM_ENV = $$(INSTALLER_ARCHIVE)
isEmpty(INSTALLER_ARCHIVE_FROM_ENV) {
    INSTALLER_ARCHIVE = $$OUT_PWD/$${BASENAME}.7z
} else {
    INSTALLER_ARCHIVE = $$OUT_PWD/$$(INSTALLER_ARCHIVE)
}

DIST_ARCHIVE_FROM_ENV = $$(DIST_ARCHIVE)
isEmpty(DIST_ARCHIVE_FROM_ENV) {
    DIST_ARCHIVE_FROM_ENV = $$shell_path($$OUT_PWD/$${BASENAME}.7z)
} else {
    DIST_ARCHIVE_FROM_ENV = $$shell_path($$OUT_PWD/$$(DIST_ARCHIVE))
}

linux {
    bindist.commands = 7z a -mx9 \"$$DIST_ARCHIVE_FROM_ENV\" \"$$FGAP_INSTALL_PATH\"
    QMAKE_EXTRA_TARGETS += bindist
}

QMAKE_EXTRA_TARGETS += deployqt deploy_ext_qml deploy_all

