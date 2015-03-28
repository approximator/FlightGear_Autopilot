import QtQuick 2.3
import Material 0.1
import FGear 0.1

ApplicationWindow {
    id: fgview
    visible: true

    theme {
        accentColor: "#009688"
    }

    initialPage: page


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

            FgAircraftsView {
                id: aircraftsView
                width: parent.width
                height: page.height
                fgController: fg_controller
            }
        }

        Loader {
            anchors {
                left: sidebar.right
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }

            source: Qt.resolvedUrl(aircraftsView.currentAiPagePath)
            asynchronous: true
        }
    }
}
