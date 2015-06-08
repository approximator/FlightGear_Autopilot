import qbs 1.0

Product {
    property string qmlFilesPath: "modules"
    property string moduleName: "FGear"

    Group {
        name: "QmlModules"
        files: [
           "modules/FGear",
            "/Users/andrey/Project/GitHub/qml-extras/modules/Material",
            "/Users/andrey/Project/GitHub/qml-material/modules/Material"
        ]
        qbs.install: true
        qbs.installDir: project.fgap_qml_modules_path
    }
}
