QML_MODULES_RELATIVE_PATH = $$relative_path($$FGAP_QML_MODULES_PATH, $$FGAP_BIN_PATH)
message (QML_MODULES_RELATIVE_PATH == $$QML_MODULES_RELATIVE_PATH)
DEFINES += FGAP_QML_MODULES_PATH='\\"$$QML_MODULES_RELATIVE_PATH\\"'

macx:{
    FGAP_QML_MODULES_PATH = $$relative_path($$FGAP_QML_MODULES_PATH, $$FGAP_BUNDLE_PATH)
}
message (FGAP_QML_MODULES_PATH == $$FGAP_QML_MODULES_PATH)

!isEmpty(EXTERNAL_MODULES_PATH) {
    qml-material.files = $$EXTERNAL_MODULES_PATH/qml-material/modules/Material
    qml-material.path = $$FGAP_QML_MODULES_PATH

    qml-extras.files = $$EXTERNAL_MODULES_PATH/qml-extras/modules/Material/Extras
    qml-extras.path = $$FGAP_QML_MODULES_PATH/Material
}

    qml-fgear.files = qml-fgear/modules/FGear
    qml-fgear.path = $$FGAP_QML_MODULES_PATH

QML_MODULES_DIRS = \
                    qml-material \
                    qml-extras \
                    qml-fgear

macx:{
    QMAKE_BUNDLE_DATA += $$QML_MODULES_DIRS
} else {
#linux
    INSTALLS += qml-fgear
}
