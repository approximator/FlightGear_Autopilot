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

    FgapQmlModule {
        name: "qml_material_components"
        moduleName: "Material/Components"
        moduleRootDir: "/tmp/qml-material-components"
        sourceUrl: "https://github.com/AndreyShelest/qml-material-components.git"

        sourceFiles: [
            "Material/Components/*qml*"
        ]
    }

    references: [
        "qml-fgear/qml-fgear.qbs"
    ]

}
