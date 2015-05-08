import QtQuick 2.2
import FGear 0.1
import Material 0.1
import Material.Components 0.1 as MGui

MGui.MainWindow {

    title: "Autopilot Test"

    View {
        anchors.fill: parent
        anchors.margins: units.dp(20)
        elevation: 1

        FgAutopilot {}
    }

}
