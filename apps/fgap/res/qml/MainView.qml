import QtQuick 2.3
import FGear 0.1
import Material.Components 0.1 as MGui

MGui.MainWindow {
    id: fgview

    title: "Flight Gear Autopilot"

    width: 1280
    height: 768

    leftSidebarContent: FgAircraftsView {
        fgController: fg_controller
    }

}
