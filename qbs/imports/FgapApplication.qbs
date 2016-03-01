import qbs
import qbs.FileInfo

Product {
    type: "application" // no Mac app bundle

    Depends { name: "cpp" }
    cpp.cxxLanguageVersion: "c++14"
    cpp.warningLevel: "all"
    cpp.treatWarningsAsErrors: false
    cpp.linkerFlags: {
        var flags = [];
        if (qbs.buildVariant == "release" && (qbs.toolchain.contains("gcc") || qbs.toolchain.contains("mingw")))
            flags.push("-Wl,-s");
        return flags;
    }
    cpp.minimumOsxVersion: "10.7"
    cpp.minimumWindowsVersion: qbs.architecture === "x86" ? "5.1" : "5.2"
    cpp.visibility: "minimal"
    cpp.rpaths: qbs.targetOS.contains("osx")
            ? ["@executable_path/../lib"]
            : ["$ORIGIN/../lib"]

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
