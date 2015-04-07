import qbs.base 1.0

Application {
    name: project.fgap_app_target
    consoleApplication: qbs.debugInformation

    Depends { name: "cpp" }
    cpp.defines: project.generalDefines
    cpp.cppFlags: "-std=c++11"

    cpp.rpaths: qbs.targetOS.contains("osx") ? ["@executable_path/.."]
                                             : ["$ORIGIN/../" + project.libDirName +  "/qtcreator"]
//    cpp.includePaths: [
//        fgap.sharedSourcesDir + "/qtsingleapplication",
//        fgap.sharedSourcesDir + "/qtlockedfile",
//    ]

    Depends { name: "Qt"; submodules: ["widgets", "qml", "quick", "gui", "network", "xml", "svg"] }

    Group {
        name: "Sources"
        files: 'src/*.cpp'
    }

    Group {
        name: "Headers"
        files: 'src/*.h'
    }

    Group {
        name: "Resources"
        files: 'res/qml/qml_res.qrc'
    }

    Group {
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: project.fgap_app_path
    }
}
