import qbs
import qbs.FileInfo

Product {
    type: "copied_qml_module"
    name: "qml_fgear"

    Depends { name: "copyable_qml_module" }
    copyable_qml_module.targetDirectory: FileInfo.joinPaths(
        project.fgapInstallRoot,
        project.fgapInstallDir,
        project.fgapQmlInstallDir
    )
    copyable_qml_module.moduleSrcRoot: FileInfo.joinPaths(
        sourceDirectory,
        "modules"
        )

    Group {
        name: "qml_sources"
        fileTags: ["copyable_qml_module"]
        prefix: "modules/FGear/"
        files: [
            "*qml*",
            "AutopilotItems/*qml*",
            "flight_pic/*flight_pic/*",
            "js/*.js",
            "ListItems/*",
            "Pointers/*.qml",
            "Pointers/pictorial_navigation_indicator/*.png",
            "SettingsItems/*qml*"
        ]
    }
}
