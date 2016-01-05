import qbs
import qbs.FileInfo
import FgapFunctions

Product {
    type: "copied_qml_module"

    property string moduleName
    property string moduleSrcPrefix: "modules"
    property path moduleSrcDir: moduleSrcPrefix + "/" + moduleName +"/"
    property path moduleRootDir: sourceDirectory //Search or download dIr
    property string sourceUrl
    property stringList sourceFiles: []

    Depends { name: "copyable_qml_module" }
    copyable_qml_module.targetDirectory: FileInfo.joinPaths(
        project.fgapInstallRoot,
        project.fgapInstallDir,
        project.fgapQmlInstallDir
    )
    copyable_qml_module.moduleSrcRoot: FileInfo.joinPaths(
        moduleRootDir,
        moduleSrcPrefix
        )

    Group {
        name: "qmlModule"
        fileTags: ["copyable_qml_module"]
        prefix: moduleRootDir + "/" + moduleSrcPrefix + "/"
        files: product.sourceFiles
    }
}
