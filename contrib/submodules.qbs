import qbs
import qbs.FileInfo
import qbs.ModUtils

Project {
    name: "contrib_projects"

    FgapQmlModule {
        name: "qml_material"
        srcPrefix: "qml-material/modules"

        files: [
            "qml-material/modules/Material/*",
            "qml-material/modules/Material/Extras",
            "qml-material/modules/Material/fonts",
            "qml-material/modules/Material/icons",
            "qml-material/modules/Material/ListItems/*",
            "qml-material/modules/QtQuick/"
        ]

    }

    references: [
        "qt-qml-models/QtQmlModels.qbs",
        "qt-super-macros/QtSuperMacros.qbs",
    ]

}
