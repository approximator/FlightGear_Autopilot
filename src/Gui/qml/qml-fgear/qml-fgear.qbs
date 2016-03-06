import qbs
import qbs.FileInfo

QmlModule {
    name: "qml_fgear"

    srcPrefix: "modules"
    targetDirectory: FileInfo.joinPaths(
                         project.appInstallRoot,
                         project.appInstallDir,
                         project.appQmlInstallDir
                         )

    files: [
        "modules/FGear/*qml*",
        "modules/FGear/AutopilotItems/*qml*",
        "modules/FGear/flight_pic/*",
        "modules/FGear/js/*.js",
        "modules/FGear/ListItems/*",
        "modules/FGear/Pointers/*.qml",
        "modules/FGear/Pointers/pictorial_navigation_indicator/*.png",
        "modules/FGear/SettingsItems/*qml*"
    ]
}
