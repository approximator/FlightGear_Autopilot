import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import FGear 0.1
import FGear.AutopilotItems 0.1

FocusScope {
    id: autopilot

    anchors.centerIn: parent
    width: Units.dp(800)
    height: Units.dp(250)

    Rectangle {
        anchors.fill: parent
        color: "gray"
        opacity: 0.8
        radius: Units.dp(5)
        border.color: Qt.darker(color)
        border.width: Units.dp(3)

    }

    AutopilotModel { id: _autopilotModel }

    GridLayout {
        columns: 10
        rows: 3
        rowSpacing: Units.dp(32)
        columnSpacing: Units.dp(32)

        anchors.rightMargin: Units.dp(20)
        anchors.leftMargin: Units.dp(20)
        anchors.topMargin: Units.dp(16)
        anchors.bottomMargin: Units.dp(16)

        anchors.fill: parent

        Repeater {
            id: _buttons
            model: _autopilotModel

            Loader {
                Layout.row: row
                Layout.rowSpan: rowSpan
                Layout.column: column
                Layout.columnSpan: columnSpan
                Layout.fillHeight: true
                Layout.fillWidth: true

                asynchronous: true // Check this later
                source: itemSource;
            }
        }
    }
}
