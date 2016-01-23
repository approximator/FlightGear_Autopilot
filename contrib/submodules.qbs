import qbs
import qbs.FileInfo
import qbs.ModUtils

Project {
    name: "contrib_projects"

    Product {
        type: "copied_qml_module"
        name: "qml_material"

        Depends { name: "copyable_qml_module" }
        copyable_qml_module.targetDirectory: FileInfo.joinPaths(
                                                 project.fgapInstallRoot,
                                                 project.fgapInstallDir,
                                                 project.fgapQmlInstallDir
                                                 )
        copyable_qml_module.moduleSrcRoot: FileInfo.joinPaths(
                                               sourceDirectory,
                                               "qml-material/modules"
                                               )

        Group {
            name: "qml_sources"
            fileTags: ["copyable_qml_module"]
            prefix: "qml-material/modules/"
            files: [
                "Material/*",
                "Material/Extras",
                "Material/fonts",
                "Material/icons",
                "Material/ListItems/*",
                "QtQuick/"
            ]
        }

        FgapSubmoduleProbe {
            moduleName: "qml-material"
            gitRootDir: project.fgapSourceRoot
        }
    }

    references: [
        "qt-qml-models/QtQmlModels.qbs",
        "qt-super-macros/QtSuperMacros.qbs",
        "ardupilot.qbs",
    ]

}
