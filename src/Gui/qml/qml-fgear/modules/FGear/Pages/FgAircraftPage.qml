import QtQuick 2.7
import QtQuick.Controls 2.0

import FGear 0.1
import FGear.Controls 0.1
import FGear.Components.Autopilot 0.1

FgPage {

    objectName: "AircraftPage"
    id: fgAircraftPage

    title: qsTr("Aircraft control")

    property var aircraft: null
    readonly property bool active: (aircraft !== null)

    FgLabel {
        id: callsignLabel

        anchors.top: parent.top
        anchors.left: parent.left
        topPadding: AppConfig.dp(10)
        leftPadding: AppConfig.dp(10)

        text: qsTr("Select aircraft")
        styleName: "display2"
    }

    FgAutopilotView { id: autopilot }
    Connections {
        enabled: active
        target: autopilot
        onAutopilotEngage: aircraft.autopilotEngage(activate)
    }

    states: State {
        name: "active"
        when: active

        PropertyChanges { target: callsignLabel; text: aircraft.callsign }
    }
}
