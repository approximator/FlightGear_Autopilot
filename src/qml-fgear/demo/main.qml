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
                fgController: controller
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

    QtObject {
        id: controller
        signal aircraftConnected(var aircraft);
    }

    Timer {
        property int counter: 0
        id: controllerTimer
        interval: 2000; running: false; repeat: true
        onTriggered: {
           if (counter < 5) {
               var obj = {};
               obj.callsign = Date().toString();
               obj.params = {
                   name: "blabla",
                   angle: 13
               }
               controller.aircraftConnected(obj);
               counter+=1;
           } else {
               stop();
           }
        }
    }
Component.onCompleted: controllerTimer.start()
}
