import QtQuick 2.2
import Material 0.1
import fgap 1.0

ApplicationWindow {
    id: fgap

    visible: true
    title: "Flight Gear Autopilot"

    width: 1280
    height: 720


    theme {
        primaryColor: Palette.colors["blue"]["500"]
        primaryDarkColor: Palette.colors["blue"]["700"]
        accentColor: Palette.colors["teal"]["500"]
        tabHighlightColor: "white"
    }

    FgAircraftsModel {
        id: fgapModel
    }

    FgInitialPage {
        id: startpage
        aircraftsModel: fgapModel
    }

    initialPage: startpage
}
