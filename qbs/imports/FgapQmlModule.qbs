import qbs
import qbs.FileInfo


Product {
    type: "copied_resource"

    property string srcPrefix: "modules"

    Depends { name: "copyable_resource" }
    copyable_resource.prefix: srcPrefix
    copyable_resource.targetDirectory: FileInfo.joinPaths(
                                           project.fgapInstallRoot,
                                           project.fgapInstallDir,
                                           project.fgapQmlInstallDir
                                           )

}
