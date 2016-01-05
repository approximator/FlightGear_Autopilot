import qbs 1.0
import qbs.FileInfo

import FgapFunctions

Probe {
    // Inputs
    property path gitRootDir: sourceDirectory
    property path moduleName
    property path moduleSrcDir: FileInfo.joinPaths(sourceDirectory, moduleName)

    configure: {
        if (!moduleName)
            throw('"moduleName" must be specified');
        found = FgapFunctions.loadModule(moduleName, moduleSrcDir, gitRootDir);
    }
}
