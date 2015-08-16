var File = loadExtension("qbs.File");
var FileInfo = loadExtension("qbs.FileInfo");
// var ModUtils = loadExtension("qbs.ModUtils");
var Process = loadExtension("qbs.Process");

function getModuleFiles(product) {
    var files = product.sourceFiles;
    var moduleName = product.name.replace(/_/g, "-");
    var moduleDir = product.moduleRootDir;
    if (File.exists(moduleDir)) {
        /* check updates of the module */
    } else {
        /* Try to load module from url */
        var url = product.sourceUrl;
        if (!url) {
            throw("[" + moduleName + "] Invalid module Url");
        }
        loadModule(moduleName, moduleDir, url);
    }
    // files.push(FileInfo.joinPaths(moduleDir, product.moduleSrcDir))
    // files.push(FileInfo.joinPaths(moduleDir, product.moduleSrcDir) + "/*.qml");
    // files.push(FileInfo.joinPaths(moduleDir, product.moduleSrcDir) + "qmldir")
    // files.push(FileInfo.joinPaths(moduleDir, product.moduleSrcDir) + "*.js")
    return files;
}

function loadModule(moduleName, moduleDir, url) {
    var process = new Process();
    var command = "git";
    var args = [ "clone", url, moduleDir ];
    try {
        process.exec(command, args, true);
        print("Cloning module [ " + moduleName + "] from URL [ " + url + " ]");
    } catch (e) {
        print("Cloning module error:  " + e);
    }
}
