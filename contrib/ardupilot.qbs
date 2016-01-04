Product {
    type: "staticlibrary"
    name: "ArdupilotLib"

    Export {
        Depends { name: "cpp" }

        cpp.cxxLanguageVersion: "c++11"

        cpp.includePaths: [
            "ardupilot/libraries",
        ]


        cpp.defines: [
            'TOOLCHAIN=NATIVE',
            'HAL_BOARD=HAL_BOARD_SITL',
            'HAL_BOARD_SUBTYPE=HAL_BOARD_SUBTYPE_NONE',
            'CONFIG_HAL_BOARD=HAL_BOARD',
            'CONFIG_HAL_BOARD_SUBTYPE=HAL_BOARD_SUBTYPE',
        ]
    }

    files: [
        "ardupilot/libraries/AP_Common/AP_Common.cpp",
        "ardupilot/libraries/AP_Common/AP_Common.h",
        "ardupilot/libraries/AP_HAL/AP_HAL_Boards.h",

        "ardupilot/libraries/AP_Math/*.h",
        "ardupilot/libraries/AP_Math/*.cpp",
    ]
}
