import QtQuick 2.2
import Material 0.1
import fgap 1.0


ApplicationWindow {
    id: fgap
    property string themeStyle: "dark" //default or dark

    title: "Flight Gear Autopilot"

    width: 1280
    height: 720
    visible: true

    theme {
        primaryColor: Palette.colors["blueGrey"]["500"]
        accentColor: Palette.colors["cyan"]["500"]
    }
    Component.onCompleted: {
        if (themeStyle === "dark") {
            Theme.light.light = false;
            theme.primaryColor = Palette.colors["blueGrey"]["500"];
            theme.primaryDarkColor = Palette.colors["grey"]["900"];
            theme.accentColor = Palette.colors["cyan"]["500"]
        } else {
            Theme.light.light = true;
            theme.primaryColor = Palette.colors["blue"]["500"];
            theme.primaryDarkColor = Palette.colors["blueGrey"]["700"];
            theme.accentColor = Palette.colors["teal"]["500"]
        }

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
