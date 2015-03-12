!isEmpty(FGAP_PRI_INCLUDED):error("fgap.pri already included")
FGAP_PRI_INCLUDED = 1

CLOUDREMOTE_VERSION = 0.0.2
CONFIG += c++11

FGAP_SOURCE_TREE = $$PWD

defineReplace(cleanPath) {
    win32:1 ~= s|\\\\|/|g
    contains(1, ^/.*):pfx = /
    else:pfx =
    segs = $$split(1, /)
    out =
    for(seg, segs) {
        equals(seg, ..):out = $$member(out, 0, -2)
        else:!equals(seg, .):out += $$seg
    }
    return($$join(out, /, $$pfx))
}

isEmpty(FGAP_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    FGAP_BUILD_TREE = $$cleanPath($$OUT_PWD)
    FGAP_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

FGAP_APP_PATH = $$FGAP_BUILD_TREE/bin

macx {
    FGAP_APP_TARGET    = "FlightGearAutopilot"
    FGAP_BUNDLE_PATH = $$FGAP_APP_PATH/$${FGAP_APP_TARGET}.app
    FGAP_LIBRARY_PATH = $$FGAP_BUNDLE_PATH/Contents/PlugIns
    FGAP_DATA_PATH    = $$FGAP_BUNDLE_PATH/Contents/Resources
    FGAP_DOC_PATH     = $$FGAP_DATA_PATH/doc
    FGAP_BIN_PATH     = $$FGAP_BUNDLE_PATH/Contents/MacOS
    FGAP_QML_MODULES_PATH = $$FGAP_BUNDLE_PATH/Contents/Imports/qtquick2
} else {
    FGAP_APP_TARGET   = fgautopilot
    FGAP_LIBRARY_PATH = $$FGAP_BUILD_TREE/lib/fgautopilot
    FGAP_LIBEXEC_PATH = $$FGAP_APP_PATH
    FGAP_DATA_PATH    = $$FGAP_BUILD_TREE/share/fgautopilot
    FGAP_DOC_PATH     = $$FGAP_BUILD_TREE/share/doc/fgautopilot
    FGAP_BIN_PATH     = $$FGAP_APP_PATH
    FGAP_QML_MODULES_PATH = $$FGAP_DATA_PATH/Imports/qtquick2
}

INCLUDEPATH += \
    $$FGAP_SOURCE_TREE/src/libs

CONFIG += depend_includepath

#LIBS += -L$$FGAP_LIBRARY_PATH
#DEFINES += FGAP_LIBRARY_BASENAME=\\\"$$FGAP_LIBRARY_BASENAME\\\"

unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug-shared
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release-shared

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

qt:greaterThan(QT_MAJOR_VERSION, 4) {
    contains(QT, gui): QT += widgets
}
