import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import FGear 0.1
import FGear.AutopilotItems 0.1

FocusScope {
    id: autopilot

    anchors.centerIn: parent
    width: parent.width
    height: width / 3

    property bool engaged: false
    property string currentMode

    signal buttonChecked (string btn_name, string mode, bool checked)

    signal autopilotEngage (bool activate)
    signal modeChanged (string mode)
    signal altitudeChanged (int altitude)
    signal vesticalSpeedChanged (int vspeed)

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

                asynchronous: false // Check this later
                source: itemSource;
            }
        }
    }

    onEngagedChanged: {
        _buttons.itemAt(0).item.checked = engaged;
        _autopilotModel.get(_autopilotModel.count-2).itemTextColor = engaged ?
                    Palette.colors["deepOrange"]["600"] : Palette.colors["grey"]["700"]
    }

    onButtonChecked: {
        if (btn_name.indexOf("engage") != -1)
        {
            engaged = checked;
            autopilotEngage(checked);
        }
        else if (btn_name.indexOf("mode") != -1)
        {
            modeChanged(mode);
        }
        else if (btn_name.indexOf("trim") != -1)
        {
            var sign = btn_name.indexOf("up") > 0 ? 1 : -1;
            vesticalSpeedChanged(sign * 10);
        }
        else if (btn_name.indexOf("knobs") != -1)
        {
            altitudeChanged(altitude)
        }
    }
}
