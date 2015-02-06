import QtQuick 2.3
import Material 0.1
import Material.ListItems 0.1 as ListItem

ApplicationWindow {
    id: fgview
    visible: true

    theme {
        accentColor: "#009688"
    }

    initialPage: page

    ListModel {
        id: aircrafts
    }

    Connections {
        target: fgController
        onAircraftConnected: {
            aircrafts.append({"callsign": aircraft.callsign});
        }
    }

    Page {
        id: page

        title: "Fg Aircrafts View"

        actions: [
            Action {
                iconName: "content/add"
            },

            Action {
                iconName: "action/search"
                name: "Search"
            },

            Action {

                iconName: "action/language"
                name: "Language"
            },

            Action {
                iconName: "action/account_circle"
                name: "Account"
            },

            Action {
                iconName: "action/settings"
                name: "Settings"
            }
        ]

        Sidebar {
            id: sidebar

            Column {
                width: parent.width

                Repeater {
                    model: aircrafts
                    delegate: ListItem.Standard {
                        text: callsign
//                        selected: modelData == selectedComponent
//                        onTriggered: selectedComponent = modelData
                    }
                }
            }
        }

//        Loader {
//            anchors {
//                left: sidebar.right
//                right: parent.right
//                top: parent.top
//                bottom: parent.bottom
//            }

//            // selectedComponent will always be valid, as it defaults to the first component
//            source: Qt.resolvedUrl("%1Demo.qml").arg(selectedComponent.replace(" ", ""))
//            asynchronous: true
//        }
    }
}
