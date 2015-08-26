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
            iconName: "content/add"
            name: "Add aircraft"
            hoverAnimation: true
            enabled: true
//            onTriggered: pageStack.push(Qt.resolvedUrl("FgMap.qml"), { airmodel: menuList.model })
        },
        Action {
            iconName: "maps/map"
            name: "Aircrafts map"
            hoverAnimation: true
            enabled: true
            onTriggered: pageStack.push(Qt.resolvedUrl("FgMap.qml"), { airmodel: menuList.model })
        },
        Action {
            iconName: "action/settings"
            name: "Page Settings"
            hoverAnimation: true
            onTriggered: rightSidebar.showing = !rightSidebar.showing
        }
    ]

    rightSidebar: PageSidebar {
        width: Units.dp(250)
        showing: false
        actionBar.title: fgAircraft.callsign
        actionBar.backgroundColor: Qt.darker(theme.primaryColor)

        actions: [
            Action {
                iconName: "action/info"
                name: "Info"
                onTriggered: notify("Info Action")
            },
            Action {
                iconName: "content/clear"
                name: "Close page settings"
                onTriggered: rightSidebar.showing = false
            }
        ]

        sidebar: Button {
            text: "Run"
            elevation: 1
            enabled: fgAircraft.flightgearReady
            onClicked: fgAircraft.runFlightGear()
        }
    }

    /*Left side menu*/
    Sidebar {
        id: _sidebar
        header: "Aircrafts menu"
        width: Units.dp(350)
        backgroundColor: Palette.colors["grey"]["200"]
        contents: menuList
    }

    ListView {
        id: menuList

        width: _sidebar.width
        height: childrenRect.height
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
                onFgInfoClicked: rightSidebar.showing = !rightSidebar.showing
                Component.onCompleted: {
                    if (index === 0) {
                        aircraftsPage.fgAircraft = aircraft;
                    }
                }
            }
        }
    }

    FgAircraftPage {
        anchors {
            left: _sidebar.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        aircraft: fgAircraft
    }

}
