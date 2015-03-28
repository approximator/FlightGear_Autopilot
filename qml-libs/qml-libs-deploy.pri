# Additional import path used to resolve QML modules in Qt Creator's code model
# EXTERNAL_MODULES_PATH - path to external qml sources.
# If it is empty, needed modules will be search in default $$[QT_INSTALL_QML] path.
EXTERNAL_MODULES_PATH =
ModVersion = 0.0.5
QML_MODULES = \
                    qml-material \
                    qml-extras \
                    qml-fgear


QML_MODULES_RELATIVE_PATH = $$relative_path($$FGAP_QML_MODULES_PATH, $$FGAP_BIN_PATH)
message (QML_MODULES_RELATIVE_PATH == $$QML_MODULES_RELATIVE_PATH)
DEFINES += FGAP_QML_MODULES_PATH='\\"$$QML_MODULES_RELATIVE_PATH\\"'

macx: {
    FGAP_QML_MODULES_PATH = $$relative_path($$FGAP_QML_MODULES_PATH, $$FGAP_BUNDLE_PATH)
}

isEmpty(EXTERNAL_MODULES_PATH):{

    message("Need to load external qml modules")
    load_script = $$system_path($$clean_path($$PWD/../scripts/load_qml_module.sh))

!exists($$OUT_PWD/qml-material): system(cd $$OUT_PWD && $$load_script qml-material "https://github.com/papyros/qml-material/archive/v$${ModVersion}.zip")
!exists($$OUT_PWD/qml-extras): system(cd $$OUT_PWD && $$load_script qml-extras "https://github.com/papyros/qml-extras/archive/v$${ModVersion}.zip")


    QMAKE_EXTRA_TARGETS += forceqmake
    forceqmake.target = $(MAKEFILE)
    forceqmake.depends = FORCE

    EXTERNAL_MODULES_PATH = $$OUT_PWD
}

    qml-material.files = $$EXTERNAL_MODULES_PATH/qml-material/modules/Material
    qml-material.path = $$FGAP_QML_MODULES_PATH

    qml-extras.files = $$EXTERNAL_MODULES_PATH/qml-extras/modules/Material/Extras
    qml-extras.path = $$FGAP_QML_MODULES_PATH/Material

    qml-fgear.files = $$PWD/qml-fgear/modules/FGear
    qml-fgear.path = $$FGAP_QML_MODULES_PATH

macx: {
    QMAKE_BUNDLE_DATA += $$QML_MODULES
} else {
#    linux
    INSTALLS += $$QML_MODULES
}
