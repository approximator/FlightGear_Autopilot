import qbs
import qbs.FileInfo

FgapQmlModule {
    name: "qml_fgear"

    files: [
        "modules/FGear/*qml*",
        "modules/FGear/AutopilotItems/*qml*",
        "modules/FGear/flight_pic/*flight_pic/*",
        "modules/FGear/js/*.js",
        "modules/FGear/ListItems/*",
        "modules/FGear/Pointers/*.qml",
        "modules/FGear/Pointers/pictorial_navigation_indicator/*.png",
        "modules/FGear/SettingsItems/*qml*"
    ]
}
