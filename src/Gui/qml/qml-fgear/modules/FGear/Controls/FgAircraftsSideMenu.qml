import QtQuick 2.7

import QtQuick.Controls 2.0

import FGear 0.1
import FGear.ListItems 0.1

FgListSideMenu {
    id: listSideMenu

    objectName: "aircraftsSideMenu"

    title: qsTr("Aircrafts")
    delegate: FgMenuItem {
        selected: ListView.isCurrentItem
        infoEnabled: ListView.isCurrentItem
        onFgInfoClicked: fgap.aircraft.runFlightGear()

        connected: connected
        text: callsign

        onClicked: {
            ListView.view.currentIndex = index;
//            fgap.aircraft = model.qtObject;
        }

        Component.onCompleted: {
            if (index === 0) {
//                fgap.aircraft = model.qtObject;
            }
        }
    }
}
