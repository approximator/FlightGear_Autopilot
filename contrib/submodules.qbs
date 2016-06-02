import qbs
import qbs.FileInfo
import qbs.ModUtils

Project {
    name: "contrib_projects"

    references: [
        "qt-qml-models/QtQmlModels.qbs",
        "qt-super-macros/QtSuperMacros.qbs",
        "nameit/nameit.qbs"
    ]

}
