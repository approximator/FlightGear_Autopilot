import qbs
import qbs.FileInfo

QmlModule {
    name: "qml_fgear"

    Group {
        name: "qml"
        fileTags: ["qml_import"]
        prefix: FileInfo.joinPaths(moduleSourcesDir, "/**/")
        files: ["*.qml", "*.js", "*.svg", "*.png", "*qmldir"]
    }
}
