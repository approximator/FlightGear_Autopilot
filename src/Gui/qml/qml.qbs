import qbs

Project {
    name: "qml_libs"
    FgapQmlModule {
        name: "qml_material"
        moduleName: "Material"
        moduleRootDir: "/tmp/qml-material"
        sourceUrl: "https://github.com/papyros/qml-material.git"
        sourceFiles: [
            "Material/*",
            "Material/Extras",
            "Material/fonts",
            "Material/icons",
            "Material/ListItems/*",
            "QtQuick"
        ]
    }

    references: [
        "qml-fgear/qml-fgear.qbs"
    ]
}
