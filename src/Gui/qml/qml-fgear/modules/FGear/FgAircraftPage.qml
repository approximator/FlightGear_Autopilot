import Material 0.1
import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: airPage
    width: Units.dp(100)
    height: Units.dp(200)
    color: "#f3f7fe"

    property QtObject aircraft: null

    onAircraftChanged: {
        titleLabel.text = aircraft.callsign
        autopilot.engaged = aircraft.autopilotEngaged  // TODO: check or uncheck engaged button
    }

    Label {
        id: titleLabel
        width: parent.width
        text: "none"
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
