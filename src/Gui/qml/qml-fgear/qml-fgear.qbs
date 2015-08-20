import qbs

FgapQmlModule {
    name: "qml_fgear"
    moduleName: "FGear"
    sourceFiles: [
        "*qml*",
        "AutopilotItems/*qml*",
        "flight_pic/*",
        "js/*.js",
        "Pointers/*.qml",
        "Pointers/pictorial_navigation_indicator/*.png"
    ].map(function(file) {
        //prepend moduleName as prefix to all SourceFiles
        return (moduleName + "/" + file);
      })
}
