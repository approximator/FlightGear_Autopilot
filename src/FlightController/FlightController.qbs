import qbs

FgapApplication {
    name: project.app_short_name
    targetName: fgapAppTarget
    Depends { name: "qml_fgear" }
    Depends { name: "qml_material" }
    Depends { name: "qml_material_components" }

    Depends { name: "cpp" }
    cpp.includePaths: [ "./", "utils"]
    cpp.rpaths: qbs.targetOS.contains("osx")
            ? ["@executable_path/../lib"]
            : ["$ORIGIN/../lib"]

    Depends { name: "Qt"; submodules: [ "qml", "quick", "network", "xml", "svg"] }

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
