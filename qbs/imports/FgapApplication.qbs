import qbs
import qbs.FileInfo

Application {

    property int v_major: 0
    property int v_minor: 0
    property int v_release: 3
    property string fgap_version: v_major + '.' + v_minor + '.' + v_release
    property string app_name: "FlightGear Autopilot"
    property string app_short_name: "fgautopilot"

    //Only for systems without bundle
     property path fgapInstallDir: qbs.targetOS.contains("osx") ? app_name + ".app/Contents" : app_name
    /*By default 'destinationDirectory' :
    *      Linux/Win -> product.buildDirectory/
    *      OS X -> product.buildDirectory/$$(fgapAppTarget).app/
    */
    property path fgapInstallRoot: destinationDirectory
    qbs.installRoot: fgapInstallRoot /* If you want to change global installation dir*/

    property path fgapAppTarget: qbs.targetOS.contains("osx") ? app_name : app_short_name
    property path fgapDataPath: qbs.targetOS.contains("osx")
                                   ? "Resources"
                                   : "data"

    property path fgapBinDir: qbs.targetOS.contains("osx")
                                  ? "MacOS"
                                  : "bin"
    property path fgapQmlInstallDir: FileInfo.joinPaths(fgapDataPath, "qml")
    property path fgapConfigSourceRoot: FileInfo.joinPaths(project.sourceDirectory, "../doc/config/")
    property path fgapConfigInstallDir: FileInfo.joinPaths(fgapDataPath, "config")

    property stringList generalDefines: [
        'FGAP_QML_MODULES_PATH="' + FileInfo.relativePath (fgapBinDir, fgapQmlInstallDir) + '"',
        'CONFIG_PATH="' + FileInfo.relativePath (fgapBinDir, fgapConfigInstallDir) + '"'
    ]

    property stringList generalCppFlags: []

    property string installDir

    Depends { name: "cpp" }
    cpp.defines: generalDefines.concat()
    cpp.cxxLanguageVersion: "c++11"
    cpp.warningLevel: "all"
    cpp.treatWarningsAsErrors: true
    cpp.linkerFlags: {
        var flags = [];
//throw ("!!!" + bundleName)
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
        condition: !qbs.targetOS.contains("osx")
        fileTagsFilter: product.type
        qbs.installPrefix: fgapInstallDir
        qbs.install: true
        qbs.installDir: fgapBinDir
    }

    /* Install Fgap JSON configs*/
    Group {
        fileTagsFilter: ["jsonConfigs"]
        qbs.installPrefix: fgapInstallDir
        qbs.install: true
        qbs.installDir: fgapConfigInstallDir
    }

    /* Install Fgap QML modules*/
    Group {
        fileTagsFilter: ["qmlModules"]
        qbs.installPrefix: fgapInstallDir
        qbs.install: true
        qbs.installDir: fgapQmlInstallDir
    }
}
