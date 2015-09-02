import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

Page {
    id: aircraftsPage
    property alias model: aircraftsList.model
    property QtObject fgAircraft: null

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

    tabs: [
        {
            text: "Autopilot control"
        },
        {
            text: "Instruments",
        },
    ]

    FgAircraftsList {
        id: aircraftsList
    }

    /*Left side menu*/
    Sidebar {
        id: _sidebar
        header: "Aircrafts"
        width: Units.dp(350)
        backgroundColor: Qt.lighter(Theme.primaryDarkColor)
        contents: aircraftsList
        style: "dark"
    }

    TabView {
        id: tabView
        anchors {
            left: _sidebar.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        currentIndex: aircraftsPage.selectedTab
        model: tabs
    }

    VisualItemModel {
        id: tabs

        // Tab 1 "Autopilot control"
        FgAircraftPage {
            width: tabView.width
            height: tabView.height
            color: aircraftsPage.backgroundColor
            aircraft: fgAircraft
        }

        // Tab 2 "Instruments"
        Rectangle {
            width: tabView.width
            height: tabView.height
            color: aircraftsPage.backgroundColor

            PictorialNavigation {
                width: Math.min(parent.width, parent.height)
                height: width

                heading: fgAircraft.heading
            }
        }
    }
    Component.onCompleted: {
        selectedTab = 1
    }
}
