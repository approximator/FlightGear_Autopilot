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

    Product {
        name: "qml_tricks"
        Depends { name: "Qt"; submodules: [ "qml", "quick", "gui"] }

        Export {
            Depends { name: "cpp"}
            cpp.systemIncludePaths: FileInfo.joinPaths(
                                  product.sourceDirectory,
                                  "lib-qt-qml-tricks/include"
                                  )

            Depends {
                name: "lib-qt-qml-tricks";
            }
        }
    }

    references: [
        "lib-qt-qml-tricks/src/QtLibrary.qbs",
        "ardupilot.qbs"
    ]

}
