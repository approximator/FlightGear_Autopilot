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

            FgAutopilot {
                id: fgautopilot
                onAutopilotEngage: console.log("autopilot engage state,", activate)
                onModeChanged: console.log("autopilot mode changed to,", mode)
                onAltitudeChanged: console.log("altitude changed to,", altitude)
                onVesticalSpeedChanged: console.log("vertical speed changed to,", vspeed)
            }

    }
}
