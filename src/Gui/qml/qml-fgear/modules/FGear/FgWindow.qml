import QtQuick 2.2
import Material 0.1
import fgap 1.0


ApplicationWindow {
    id: fgap

    title: "Flight Gear Autopilot"

    width: 1280
    height: 720
    visible: true


    theme {
        primaryColor: Palette.colors["blue"]["400"]
        primaryDarkColor: Palette.colors["blue"]["600"]
        accentColor: Palette.colors["teal"]["500"]
        tabHighlightColor: "white"
    }

    FgAircraftsModel {
        id: fgapModel
    }

    FgAircraftsControlPage {
        id: startpage
        model: fgapModel
    }

    initialPage: startpage
}
