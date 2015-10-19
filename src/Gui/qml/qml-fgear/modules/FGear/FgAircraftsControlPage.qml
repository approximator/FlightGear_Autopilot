import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem
import fgap 1.0

TabbedPage {
    id: aircraftsPage
    property QtObject fgAircraft: null
    property int sidebarWidth: Units.dp(350)

    title: "Aircrafts control"
    backgroundColor: Theme.primaryDarkColor

    actions: [
        Action {
            iconName: "content/add"
            name: "Add aircraft"
            hoverAnimation: true
            enabled: true
            onTriggered: aircraftsList.model.addAircraft()
        },
        Action {
            iconName: "awesome/globe"
            name: "Aircrafts map"
            hoverAnimation: true
            enabled: true
            onTriggered: pageStack.push(Qt.resolvedUrl("FgMap.qml"), { airmodel: aircraftsList.model })
        },
        Action {
            iconName: "action/settings"
            name: "Settings"
            hoverAnimation: true
            onTriggered: pageStack.push(Qt.resolvedUrl("FgSettings.qml"), { airmodel: aircraftsList.model })
        }
    ]

    /*Left side menu*/
    Sidebar {
        id: _sidebar
        header: "Aircrafts"
        width: sidebarWidth
        backgroundColor: Qt.lighter(Theme.primaryDarkColor)
        contents: FgAircraftsList {
            model: FgAircraftsModel { }
            id: aircraftsList
        }
        style: "dark"
    }

    Tab {
        title: "Autopilot control"
        FgAircraftPage {
            x: _sidebar.width
            onHeightChanged: width = parent.width - _sidebar.width
            onWidthChanged: width = parent.width - _sidebar.width
            aircraft: fgAircraft
        }
    }

    Tab {
        title: "Instruments"
        Rectangle {
            x: _sidebar.width
            onHeightChanged: width = aircraftsPage.width - _sidebar.width
            onWidthChanged: width = aircraftsPage.width - _sidebar.width
            color: aircraftsPage.backgroundColor

            PictorialNavigation {
                anchors.centerIn: parent
                width: Math.min(parent.width, parent.height)
                height: width
                heading: fgAircraft ? fgAircraft.heading : 0
            }
        }
    }
}
