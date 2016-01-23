import qbs

FgapApplication {
    name: project.app_short_name
    targetName: fgapAppTarget

    Depends { name: "Qt"; submodules: [ "qml", "quick", "gui",
            "network", "xml", "svg"] }

    Depends { name: "qml_fgear" }
    Depends { name: "qml_material" }
    Depends { name: "libqtqmltricks-qtqmlmodels" }
    Depends { name: "libqtqmltricks-qtsupermacros" }
    Depends { name: "lib_ardupilot" }

    cpp.includePaths: [".", "utils"]
    cpp.defines: project.generalDefines

    /* Main source file */
    Group {
        name: "Sources"
        files: [
            "../main.cpp",
            "*.cpp",
            "autopilot/*.cpp",
            "flightgear/*.cpp",
            "utils/*.cpp",
            "vehicle/*.cpp"
        ]
    }

    Group {
        name: "Headers"
        files: [
            "*.h",
            "autopilot/*.h",
            "flightgear/*.h",
            "utils/*.h",
            "vehicle/*.h"
        ]
    }

    Group {
        name: "Resources"
        files: "../resources/qml/qml_res.qrc"
    }

    /*Fgap JSON configs*/
    Group {
        name: "jsonConfigs"
        fileTags: ["jsonConfigs"]
        prefix: project.fgapConfigSourceRoot
        files: "*"
    }
}
