import qbs
import qbs.FileInfo

Project {
    minimumQbsVersion: "1.3"
    property string fgap_version_major: '0'
    property string fgap_version_minor: '0'
    property string fgap_version_release: '5'
    property string fgap_version: fgap_version_major + '.' + fgap_version_minor + '.' + fgap_version_release
    property path fgap_source_tree: path
    property string fgap_app_path: qbs.targetOS.contains("osx") ? "" : "bin"
    property string fgap_app_target: qbs.targetOS.contains("osx") ? "FlightGear Autopilot" : "fgautopilot"
    property string fgap_bundle_root: qbs.targetOS.contains("osx") ? fgap_app_target + ".app/Contents" : fgap_app_target
    property pathList additionalLibs: []
    property string sharedSourcesDir: path + "/src/shared"
    property string libDirName: "lib"
    property string fgap_library_path: {
        if (qbs.targetOS.contains("osx"))
            return fgap_app_target + ".app/Contents/Frameworks"
        else if (qbs.targetOS.contains("windows"))
            return fgap_app_path
        else
            return libDirName + "/fgap"
    }

    property string fgap_data_path: qbs.targetOS.contains("osx")
                                   ? fgap_app_target + ".app/Contents/Resources"
                                   : "share/fgap"
    property string fgap_libexec_path: qbs.targetOS.contains("osx")
                                      ? fgap_data_path
                                      : fgap_app_path
    property string fgap_doc_path: qbs.targetOS.contains("osx")
                                  ? fgap_data_path + "/doc"
                                  : "share/doc/fgap"
    property string fgap_bin_path: qbs.targetOS.contains("osx")
                                  ? fgap_app_target + ".app/Contents/MacOS"
                                  : fgap_app_path
    property string fgap_qml_modules_path: fgap_bundle_root +"/Imports/quick2"
    property string qml_bundle_modules_path: FileInfo.relativePath(fgap_bin_path,fgap_qml_modules_path)


    property stringList generalDefines: [
        'FGAP_LIBRARY_BASENAME="' + libDirName + '"',
        'FGAP_QML_MODULES_PATH="' + qml_bundle_modules_path + '"',
    ].concat()

    qbsSearchPaths: "qbs"

    references: [
        "apps/apps.qbs",
        "qml-libs/qml-libs.qbs"
    ]

}
