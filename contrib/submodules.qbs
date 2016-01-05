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
        condition: qml_trick_probe.found

        FgapSubmoduleProbe {
            id: qml_trick_probe
            moduleName: "lib-qt-qml-tricks"
            gitRootDir: project.fgapSourceRoot
        }


        files: [
            "lib-qt-qml-tricks/src/*.h",
            "lib-qt-qml-tricks/src/*.cpp",
            "lib-qt-qml-tricks/include/*.h"
        ]

        Export {
            Depends { name: "cpp" }
            cpp.includePaths: FileInfo.joinPaths(
                                  product.sourceDirectory,
                                  "lib-qt-qml-tricks/include"
                                  )

            Depends {
                name: "lib-qt-qml-tricks";
                condition: qml_trick_probe.found;
            }
        }
    }

    SubProject {
        inheritProperties: true
        filePath: "lib-qt-qml-tricks/src/QtLibrary.qbs"
    }
}
