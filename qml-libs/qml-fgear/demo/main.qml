import QtQuick 2.2
import FGear 0.1
import Material.Components 0.1 as MGui
import "aircraftUtils.js" as AiUtils

MGui.MainWindow {

    title: "FGap Gui Test"

    width: 1280
    height: 768

    Component.onCompleted: {
        controllerTimer.start();
    }

    leftSidebarContent: FgAircraftsView {
        fgController: controller
    }

    /* debug objects and functions*/
    QtObject {
        id: controller

        property var aircrafts: []
        signal aircraftConnected(var aircraft);
        signal ourAircraftConnected(var aircraft);
        signal aircraftDisconnected(var aircraft);
    }

    Timer {
        property int counter: 0
        id: controllerTimer
        interval: 2000; running: false; repeat: true
        onTriggered: {
            switch (counter % 2) {
            case 0: controller.ourAircraftConnected(AiUtils.newAircraft()); break;
            case 1: controller.aircraftConnected(AiUtils.newAircraft()); break;
//            default: controller.ourAircraftConnected(AiUtils.newAircraft());
            }
            counter+=1;
//           stop();
        }
    }
}
