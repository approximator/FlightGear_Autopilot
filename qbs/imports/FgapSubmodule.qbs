import qbs
import qbs.FileInfo
import FgapFunctions

Product {
    type: "loaded_submodule"

    property path gitRootDir: FileInfo.joinPaths(sourceDirectory, "..");
    property path moduleName: name
    property path moduleSrcDir: FileInfo.joinPaths(sourceDirectory, moduleName)
    property path moduleSrcPrefix

    property pathList sourceFiles: [moduleSrcDir + "/*"]
    property string includePath
    property string qbsReference



    Group {
        name: product.name + "_submodule"
        fileTags: ["submodule_files"]
        prefix: product.moduleSrcPrefix
        files: FgapFunctions.getModuleFiles(product, project)
    }
}
