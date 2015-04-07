import QtQuick 2.2
import FGear 0.1
import "aircraftUtils.js" as AiUtils

FgWindow {

    title: "FGap Gui Test"


    QtObject {
        id: controller

        property var aircrafts: []
        signal aircraftConnected(var aircraft);
        signal ourAircraftConnected(var aircraft);
        signal aircraftDisconnected(var aircraft);
    }

    fgController: controller

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
Component.onCompleted: controllerTimer.start()
}
