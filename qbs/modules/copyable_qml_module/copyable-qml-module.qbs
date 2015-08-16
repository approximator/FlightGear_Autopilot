import qbs
import qbs.File
import qbs.FileInfo

Module {

    property path targetDirectory
    property string moduleSrcRoot

    additionalProductTypes: "deployed_qml_module"
    Rule {
        inputs: ["copyable_qml_module"]
        outputFileTags: ["copied_qml_module"]
        outputArtifacts: {
            var destinationDir = input.moduleProperty("copyable_qml_module", "targetDirectory");
            var srcDir = input.moduleProperty("copyable_qml_module", "moduleSrcRoot");
            var output;
            if (!destinationDir || !srcDir ) {
                // If the destination directory has not been explicitly set, replicate the
                // structure from the source directory in the build directory.
                destinationDir = project.buildDirectory + '/'
                        + FileInfo.relativePath(project.sourceDirectory, input.filePath);
                output = destinationDir;
            } else {
                output = FileInfo.joinPaths(destinationDir, FileInfo.relativePath(srcDir, input.filePath))
            }

            return [{
                filePath: output,
                fileTags: ["copied_qml_module"]
            }];
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "Copying " + FileInfo.fileName(input.fileName) + " -> " + output.filePath;
            cmd.highlight = "codegen";
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath); };
            return cmd;
        }
    }
}
