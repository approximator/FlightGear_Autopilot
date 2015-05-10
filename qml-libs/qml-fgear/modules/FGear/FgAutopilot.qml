import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import FGear 0.1
import FGear.AutopilotItems 0.1

FocusScope {
    id: autopilot

    anchors.centerIn: parent
    width: units.dp(800)
    height: units.dp(250)

    Rectangle {
        anchors.fill: parent
        color: "gray"
        opacity: 0.8
        radius: units.dp(5)
        border.color: Qt.darker(color)
        border.width: units.dp(3)

    }

    AutopilotModel { id: _autopilotModel }

    GridLayout {
        columns: 10
        rows: 3
        rowSpacing: units.dp(32)
        columnSpacing: units.dp(32)

        anchors.rightMargin: units.dp(20)
        anchors.leftMargin: units.dp(20)
        anchors.topMargin: units.dp(16)
        anchors.bottomMargin: units.dp(16)

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
