import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem

ListItem.Subtitled {
    signal runFlightgear(int index)

    height: visible ? (maximumLineCount == 2 ? Units.dp(72) : Units.dp(88)) : 0
    text: name

    action: Icon {
        anchors.centerIn: parent
        name: "maps/flight"
        color: (connected === true ? "green" : "gray")
        size: Units.dp(32)
    }

    subText: (connected === true ? "Connected" : "Not connected")
    interactive: true

    secondaryItem: Button {
        anchors.centerIn: parent
        text: "Run"
        onClicked: runFlightgear(index)
    }

//    Component.onCompleted: console.log(name, " | Connected", connected)
}
