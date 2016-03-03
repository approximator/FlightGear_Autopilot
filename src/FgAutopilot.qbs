import qbs
import qbs.FileInfo

Project {
    name: "fgap_project"
    property int v_major: 0
    property int v_minor: 0
    property int v_release: 3
    property string fgap_version: v_major + '.' + v_minor + '.' + v_release
    property string app_name: "FlightGear_Autopilot"
    property string app_short_name: "fgautopilot"

    property path fgapSourceRoot: FileInfo.joinPaths(sourceDirectory, "../")
    property path fgapInstallRoot: qbs.installRoot
    property path fgapInstallDir: qbs.targetOS.contains("osx")
                                   ? app_name + ".app/Contents"
                                   : app_name

    property path fgapAppTarget: qbs.targetOS.contains("osx")
                                 ? app_name
                                 : app_short_name
    property path fgapDataPath: qbs.targetOS.contains("osx")
                                   ? "Resources"
                                   : "data"

    property path fgapBinDir: qbs.targetOS.contains("osx")
                                  ? "MacOS"
                                  : ""
    property path fgapQmlInstallDir: FileInfo.joinPaths(fgapDataPath, "qml")
    property path fgapConfigSourceRoot: FileInfo.joinPaths(sourceDirectory, "../doc/config/")
    property path fgapConfigInstallDir: FileInfo.joinPaths(fgapDataPath, "config")
    property path fgapPluginsInstallDir: FileInfo.joinPaths(fgapDataPath, "plugins")

    minimumQbsVersion: "1.4"
    qbsSearchPaths: [
        FileInfo.joinPaths(fgapSourceRoot, "qbs"),
        FileInfo.joinPaths(fgapSourceRoot, "contrib/Qt-Qbs-Application/qbs")
    ]

    property bool fgapSubmodulesReady: false

    property stringList generalDefines: [
        'FGAP_QML_MODULES_PATH="' + FileInfo.relativePath (fgapBinDir, fgapQmlInstallDir) + '"',
        'FGAP_PLUGINS_PATH="' + FileInfo.relativePath (fgapBinDir, fgapPluginsInstallDir) + '"',
        'CONFIG_PATH="' + FileInfo.relativePath (fgapBinDir, fgapConfigInstallDir) + '"'
    ]

    property stringList generalCppFlags: []

    references: [
        fgapSourceRoot + "contrib/submodules.qbs",
        "FlightController/FlightController.qbs",
        "Gui/qml/qml.qbs"
    ]
}
