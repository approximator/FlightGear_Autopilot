import Material 0.1
import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    width: Units.dp(100)
    height: Units.dp(200)

    property QtObject aircraft: null

    onAircraftChanged: {
        titleLabel.text = aircraft.callsign
        autopilot.engaged = aircraft.autopilotEngaged
    }

    Label {
        id: titleLabel
        width: parent.width
        text: "Add aircraft"
        style: "display3"
    }

    FgAutopilot {
        id: autopilot
        Layout.alignment: Qt.AlignTop

        onAutopilotEngage: {
            if (aircraft) {
                aircraft.autopilotEngage(activate)
            }
        }
    }
}
