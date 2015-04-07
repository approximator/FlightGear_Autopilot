import qbs 1.0

Product {

    Group {
        name: 'FGear'
        prefix: 'qml-fgear/'
        files: [ 'modules/FGear' ]
        qbs.install: true
        qbs.installDir: project.fgap_qml_modules_path
    }

    Group {
        name: 'Material'
        prefix: '/Users/andrey/Project/GitHub/'
        files: [
            'qml-material/modules/Material',
            'qml-extras/modules/Material'
        ]
        qbs.install: true
        qbs.installDir: project.fgap_qml_modules_path
    }

//    references: [
//        "qml-fgear/qml-fgear.qbs"
//    ]
}
