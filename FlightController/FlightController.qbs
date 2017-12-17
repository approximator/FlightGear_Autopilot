import qbs

Project {
    CppApplication {
        files: [
            "flightgear/**",
            "main.cpp",
        ]

        cpp.treatWarningsAsErrors: true
        cpp.cxxLanguageVersion: "c++17"

        cpp.staticLibraries: "boost_system"

        Group {
            fileTagsFilter: product.type
            qbs.install: true
        }
    }
}
