import QtQuick 2.2
import Material 0.1
import FGear 0.1

ApplicationWindow {
    id: demo

    theme {
        accentColor: "#009688"
    }

    initialPage: page

    Page {
        id: page

        title: "Component Demo"

        Sidebar {
            id: sidebar

            FgAircraftsView {
                id: aircraftsView
                width: parent.width
                height: page.height
            }
        }

        Loader {
            anchors {
                left: sidebar.right
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }

            // selectedComponent will always be valid, as it defaults to the first component
            source: Qt.resolvedUrl(aircraftsView.currentAiPagePath)
            asynchronous: true
        }
    }
}
