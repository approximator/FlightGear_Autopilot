import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import FGear 0.1

Window {

    title: "FGap Gui Test"

    width: 320
    height: 240

    Component {
        id: fgap_window_comp
        FgWindow {
            fgController: controller
        }
    }

    Loader {
        id: fgap_loader
        asynchronous: true
        sourceComponent: fgap_window_comp
    }

    BusyIndicator {
        anchors.margins: 15
        anchors.centerIn: parent
        running: !fgap_loader.item
    }

    Component.onCompleted: {
//        controllerTimer.start();
    }

    Row {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Button {
            text: "add flight"
            onClicked: controller.ourAircraftConnected(AircraftUtils.newAircraft());
        }
        Button {
            text: "add other flight"
            onClicked: controller.aircraftConnected(AircraftUtils.newAircraft());
        }
    }

    /* debug objects and functions*/
    QtObject {
        id: controller

        property var aircrafts: []
        signal aircraftConnected(var aircraft);
        signal ourAircraftConnected(var aircraft);
        signal aircraftDisconnected(var aircraft);
        signal aircraftUpdated(var aircraft);
    }

    Timer {
        property int counter: 0
        id: controllerTimer
        interval: 2000; running: false; repeat: true
        onTriggered: {
            switch (counter % 2) {
            case 0: controller.ourAircraftConnected(AircraftUtils.newAircraft()); break;
            case 1: controller.aircraftConnected(AircraftUtils.newAircraft()); break;
            }
            counter+=1;
        }
    }
}
