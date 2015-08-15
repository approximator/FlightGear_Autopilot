import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

Page {
    id: aircraftsPage

    property alias leftMenu: menuList
    property alias model: menuList.model

    property var fgAircraft: null

    title: "Aircrafts control"

    actions: [
        Action {
            iconName: "awesome/chain"
            name: "Preferences"
            hoverAnimation: true
            enabled: true
            onTriggered: pageStack.push(Qt.resolvedUrl("FgMap.qml"), { airmodel: menuList.model })
        },
        Action {
            iconName: "action/settings"
            name: "Page Settings"
            hoverAnimation: true
            onTriggered: rightSidebar.expanded = !rightSidebar.expanded
        }
    ]

    rightSidebar: _rightSidebar
    Sidebar {
        id: _rightSidebar
        property alias actionBar: _actionBar
        expanded: false
        ActionBar {
            id: _actionBar
            title: fgAircraft.callsign
            backgroundColor: Qt.darker(theme.primaryColor)

//          See comment:  https://github.com/approximator/FlightGear_Autopilot/commit/a8468be8cd42ca3073a07ce82ee5381aaebeea67#diff-69e9115982880fa7ccd3df88eada8cc4R41
//            actions: [
//                Action {
//                    iconName: "action/info"
//                    name: "Info"
//                    onTriggered: notify("Info Action")
//                },
//                Action {
//                    iconName: "content/clear"
//                    name: "Close page settings"
//                    onTriggered: rightSidebar.expanded = false
//                }
//            ]

        }

        Button {
            text: "Run"
            elevation: 1
            enabled: fgAircraft.flightgearReady
            onClicked: fgAircraft.runFlightGear()
        }
    }
    /*Left side menu*/
    ListView {
        id: menuList

        anchors.fill: parent

        highlight: Item {
            Rectangle {
                color: theme.accentColor
                opacity: 0.7
                width: Units.dp(6)
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                    topMargin: Units.dp(10)
                    bottomMargin: Units.dp(10)
                    leftMargin: Units.dp(2)
                }
            }
        }

        clip: true
        highlightFollowsCurrentItem: true
        boundsBehavior: Flickable.StopAtBounds

        model: aircraftsModel
        delegate: _menuComponent

        Component {
            id: _menuComponent
            FgMenuItem {
                selected: ListView.isCurrentItem
                onClicked: {
                    ListView.view.currentIndex = index;
                    aircraftsPage.fgAircraft = aircraft;
                }

                infoEnabled: ListView.isCurrentItem
                onFgInfoClicked: rightSidebar.expanded = !rightSidebar.expanded
                Component.onCompleted: {
                    if (index === 0) {
                        aircraftsPage.fgAircraft = aircraft;
                    }
                }
            }
        }
    }

    FgAircraftPage {
        anchors.fill: parent
        aircraft: fgAircraft
    }

}
