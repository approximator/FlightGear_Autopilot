import QtQuick 2.2
import QtQuick.Window 2.0
import FGear 0.1
import Material 0.1

Window {

    title: "Autopilot Test"

    width: 800
    height: 600

    View {
        anchors.fill: parent
        anchors.margins: Units.dp(50)
        elevation: 2

            FgAutopilot {}
    }
}
