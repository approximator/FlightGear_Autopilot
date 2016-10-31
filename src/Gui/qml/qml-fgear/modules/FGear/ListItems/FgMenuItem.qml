import QtQuick 2.7

import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import FGear 0.1
import FGear.ListItems 0.1

MenuItem {
    height: AppConfig.dp(72)

    property string itemSource: ""

    property bool infoEnabled: false
    property bool connected: false
    property bool selected: false

    signal fgInfoClicked()

    onTriggered: menuSelected(itemSource)

//    //iconName: "maps/flight"
//    secondaryItem: IconButton {
//        anchors.centerIn: parent
//        enabled: infoEnabled
//        iconName: "maps/flight"
//        color: (connected === true ? "green" : "gray")
//        size: AppConfig.dp(32)
//        onClicked: fgInfoClicked()
//    }

//    subText: (connected === true ? "Connected" : "Not connected")
//    interactive: true
}
