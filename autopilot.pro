include(autopilot.pri)

TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS = qml-libs apps

DISTFILES += $$files(scripts/*.sh)

macx: PLATFORM = "mac"
else:win32: PLATFORM = "windows"
else:linux-*: PLATFORM = "linux-$${ARCHITECTURE}"
else: PLATFORM = "unknown"

BASENAME = $$(INSTALL_BASENAME)
isEmpty(BASENAME): BASENAME = fg-autopilot-$${PLATFORM}-$${FILIGHTGEARAUTOPILOT_VERSION}

macx {
    APPBUNDLE = "$$FGAP_BUNDLE_PATH"
    BINDIST_SOURCE = "$$FGAP_BUNDLE_PATH"
    BINDIST_INSTALLER_SOURCE = $$BINDIST_SOURCE
    deployqt.commands = $$PWD/scripts/deployqtHelper_mac.sh \"$${APPBUNDLE}\" \"$$[QT_INSTALL_TRANSLATIONS]\" \"$$[QT_INSTALL_PLUGINS]\" \"$$[QT_INSTALL_IMPORTS]\" \"$$[QT_INSTALL_QML]\"
}
# else {
#    BINDIST_SOURCE = "$(INSTALL_ROOT)$$QTC_PREFIX"
#    BINDIST_INSTALLER_SOURCE = "$$BINDIST_SOURCE/*"
#    deployqt.commands = python -u $$PWD/scripts/deployqt.py -i \"$(INSTALL_ROOT)$$QTC_PREFIX\" \"$(QMAKE)\"
#    deployqt.depends = install
#    win32 {
#        deployartifacts.depends = install
#        deployartifacts.commands = git clone "git://gitorious.org/qt-creator/binary-artifacts.git" -b $$BINARY_ARTIFACTS_BRANCH&& xcopy /s /q /y /i "binary-artifacts\\win32" \"$(INSTALL_ROOT)$$QTC_PREFIX\"&& rmdir /s /q binary-artifacts
#        QMAKE_EXTRA_TARGETS += deployartifacts
#    }
#}

INSTALLER_ARCHIVE_FROM_ENV = $$(INSTALLER_ARCHIVE)
isEmpty(INSTALLER_ARCHIVE_FROM_ENV) {
    INSTALLER_ARCHIVE = $$OUT_PWD/$${BASENAME}-installer-archive.7z
} else {
    INSTALLER_ARCHIVE = $$OUT_PWD/$$(INSTALLER_ARCHIVE)
}

bindist.depends = deployqt
bindist.commands = 7z a -mx9 $$OUT_PWD/$${BASENAME}.7z \"$$BINDIST_SOURCE\"
#bindist_installer.depends = deployqt
#bindist_installer.commands = 7z a -mx9 $${INSTALLER_ARCHIVE} \"$$BINDIST_INSTALLER_SOURCE\"

#win32 {
#    deployqt.commands ~= s,/,\\\\,g
#    bindist.commands ~= s,/,\\\\,g
#    bindist_installer.commands ~= s,/,\\\\,g
#    installer.commands ~= s,/,\\\\,g
#}

QMAKE_EXTRA_TARGETS += deployqt bindist bindist_installer
