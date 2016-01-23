import qbs
import qbs.FileInfo

StaticLibrary {
    name: "lib_ardupilot"
    targetName: "libardupilot"

    property path includePath: FileInfo.joinPaths(
                               sourceDirectory,
                               "ardupilot/libraries"
                               )

    property stringList publicDefines: [
        'TOOLCHAIN=NATIVE',
        'HAL_BOARD=HAL_BOARD_SITL',
        'HAL_BOARD_SUBTYPE=HAL_BOARD_SUBTYPE_NONE',
        'CONFIG_HAL_BOARD=HAL_BOARD',
        'CONFIG_HAL_BOARD_SUBTYPE=HAL_BOARD_SUBTYPE',
    ]

    Export {
        Depends { name: "cpp" }

        cpp.defines: product.publicDefines
        cpp.systemIncludePaths: product.includePath
    }

    Properties {
        //OS X special compiler configs
        condition: qbs.targetOS.contains("osx")
        cpp.cxxStandardLibrary: "libc++"
    }

    Depends { name: "cpp" }

    cpp.defines: publicDefines
    cpp.systemIncludePaths: includePath
    cpp.cxxLanguageVersion: "c++11"

    files: [
        "ardupilot/libraries/AP_Common/AP_Common.cpp",
        "ardupilot/libraries/AP_Common/AP_Common.h",
        "ardupilot/libraries/AP_HAL/AP_HAL_Boards.h",

        "ardupilot/libraries/AP_Math/*.h",
        "ardupilot/libraries/AP_Math/*.cpp",
    ]
}
