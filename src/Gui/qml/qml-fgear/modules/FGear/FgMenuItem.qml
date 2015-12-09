import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem

ListItem.Subtitled {
    height: Units.dp(72)
    text: model.callsign

    property bool infoEnabled: false

    signal fgInfoClicked()

    //iconName: "maps/flight"
    secondaryItem: IconButton {
        anchors.centerIn: parent
        enabled: infoEnabled
        iconName: "maps/flight"
        color: (model.connected === true ? "green" : "gray")
        size: Units.dp(32)
        onClicked: fgInfoClicked()
    }

    subText: (model.connected === true ? "Connected" : "Not connected")
    interactive: true
}
