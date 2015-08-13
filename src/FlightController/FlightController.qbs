import qbs

FgapApplication {
    targetName: fgapAppTarget
    //consoleApplication: qbs.debugInformation

    property string pathToQmlModules: project.sourceDirectory + "../../../GitHub/"
    Depends { name: "cpp" }
    cpp.includePaths: [ "./"]
    cpp.rpaths: qbs.targetOS.contains("osx") ? ["@executable_path/../lib"]
                                             : ["$ORIGIN/../lib"]

    Depends { name: "Qt"; submodules: ["widgets", "qml", "quick", "gui", "network", "xml", "svg"] }
    //https://wiki.qt.io/Qbs_Quick_Reference


    Group {
        name: "Sources"
        files: [
            "../main.cpp",
            "*.cpp"
        ]
    }

    Group {
        name: "Headers"
        files: "*.h"
    }

    Group {
        name: "Resources"
        files: "../resources/qml/qml_res.qrc"
    }

    /*Fgap JSON configs*/
    Group {
        name: "jsonConfigs"
        fileTags: ["jsonConfigs"]
        prefix: fgapConfigSourceRoot
        files: "*.json"
    }

    /* Fgap QML modules*/
    Group {
        name: "fgapQml"
        fileTags: ["qmlModules"]
        prefix: "../Gui/qml/"
        files: ["qml-fgear/modules/FGear"]
    }

    /* Material QML modules*/
    Group {
        name: "materialQml"
        fileTags: ["qmlModules"]
        prefix: pathToQmlModules + "qml-material/modules/"
        files: ["Material", "QtQuick"]
    }

    /* Material QML modules additional*/
    Group {
        name: "materialComponentsQml"
        fileTags: ["qmlModules"]
        prefix: pathToQmlModules + "qml-material-components/modules/"
        files: ["Material"]
    }
}
