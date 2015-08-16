import qbs
import qbs.FileInfo

Product {
    type: "application" // no Mac app bundle

    property stringList generalDefines: [
        'FGAP_QML_MODULES_PATH="' + FileInfo.relativePath (project.fgapBinDir, project.fgapQmlInstallDir) + '"',
        'CONFIG_PATH="' + FileInfo.relativePath (project.fgapBinDir, project.fgapConfigInstallDir) + '"'
    ]

    property stringList generalCppFlags: []

    Depends { name: "cpp" }
    cpp.defines: generalDefines.concat()
    cpp.cxxLanguageVersion: "c++11"
    cpp.warningLevel: "all"
    cpp.treatWarningsAsErrors: true
    cpp.linkerFlags: {
        var flags = [];
        if (qbs.buildVariant == "release" && (qbs.toolchain.contains("gcc") || qbs.toolchain.contains("mingw")))
            flags.push("-Wl,-s");
        return flags;
    }
    cpp.minimumOsxVersion: "10.7"
    cpp.minimumWindowsVersion: qbs.architecture === "x86" ? "5.1" : "5.2"
    cpp.visibility: "minimal"
    Properties {
        //OS X special compiler configs
        condition: qbs.targetOS.contains("osx")
        cpp.cxxStandardLibrary: "libc++"
    }

    Depends { name: "Qt.core" }

    Group {
        fileTagsFilter: "application"
        qbs.installPrefix: project.fgapInstallDir
        qbs.install: true
        qbs.installDir: project.fgapBinDir
    }

    /* Install Fgap JSON configs*/
    Group {
        fileTagsFilter: ["jsonConfigs"]
        qbs.installPrefix: project.fgapInstallDir
        qbs.install: true
        qbs.installDir: project.fgapConfigInstallDir
    }

}
