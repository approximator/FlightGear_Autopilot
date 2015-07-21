include(main.pri)

TEMPLATE = subdirs
CONFIG   += ordered
SUBDIRS  = FlightController # Gui

DISTFILES += $$files($$SCRIPTS_DIR/*.sh) $$files($$SCRIPTS_DIR/*.py)
DISTFILES += $$files($$CONFIGS_DIR/*.json)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/*.qml)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/AutopilotItems/*.qml)
DISTFILES += $$files($$ROOT_DIR/Gui/qml/qml-fgear/modules/FGear/Pointers/*.qml)

macx: PLATFORM = "mac"
else:win32: PLATFORM = "windows"
else:linux-*: PLATFORM = "linux-$$QT_ARCH"
else: PLATFORM = "unknown"

BASENAME = $$(INSTALL_BASENAME)
isEmpty(BASENAME): BASENAME = fg-autopilot-$${PLATFORM}-$${FILIGHTGEARAUTOPILOT_VERSION}

PYTHON = $$findPython()
BUILD_TYPE = Release
CONFIG(debug, debug|release) {
    BUILD_TYPE = Debug
}

macx {
    APPBUNDLE = "$$FGAP_BUNDLE_PATH"
    BINDIST_SOURCE = "$$FGAP_BUNDLE_PATH"
    BINDIST_INSTALLER_SOURCE = $$BINDIST_SOURCE
    deployqt.commands = $$SCRIPTS_DIR/deployqtHelper_mac.sh \"$${APPBUNDLE}\" \"$$[QT_INSTALL_QML]\"
}
else {
    BINDIST_SOURCE = "$$FGAP_INSTALL_PATH"
    BINDIST_INSTALLER_SOURCE = "$$BINDIST_SOURCE/*"

    deployqt.commands = $$PYTHON -u $$shell_path(\"$$SCRIPTS_DIR/deployqt.py\") \
                                    $$shell_path(\"$$BINDIST_SOURCE\") $$shell_path(\"$(QMAKE)\") \
                                    \"$$BUILD_TYPE\"
    deployqt.depends = install
}


deploy_ext_qml.commands = $$PYTHON -u $$shell_path(\"$$SCRIPTS_DIR/load_qml_modules.py\") \
                                      $$shell_path(\"$$ROOT_DIR/Gui/qml\") $$shell_path(\"$$FGAP_QML_MODULES_PATH\")
deploy_ext_qml.depends = deployqt

deploy_all.depends = deploy_ext_qml

INSTALLER_ARCHIVE_FROM_ENV = $$(INSTALLER_ARCHIVE)
isEmpty(INSTALLER_ARCHIVE_FROM_ENV) {
    INSTALLER_ARCHIVE = $$OUT_PWD/$${BASENAME}-installer-archive.7z
} else {
    INSTALLER_ARCHIVE = $$OUT_PWD/$$(INSTALLER_ARCHIVE)
}

DIST_ARCHIVE_FROM_ENV = $$(DIST_ARCHIVE)
isEmpty(DIST_ARCHIVE_FROM_ENV) {
    DIST_ARCHIVE_FROM_ENV = $$OUT_PWD/$${BASENAME}.7z
} else {
    DIST_ARCHIVE_FROM_ENV = $$OUT_PWD/$$(DIST_ARCHIVE)
}

linux {
    #bindist.depends = deploy_all
    bindist.commands = 7z a -mx9 \"$$DIST_ARCHIVE_FROM_ENV\" \"$$BINDIST_SOURCE/bin\" \"$$BINDIST_SOURCE/lib\"
    QMAKE_EXTRA_TARGETS += bindist
}

QMAKE_EXTRA_TARGETS += deployqt deploy_ext_qml deploy_all

