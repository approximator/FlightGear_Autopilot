import QtQuick 2.7

import QtQuick.Controls 2.0

import FGear 0.1
import FGear.Pages 0.1
import FGear.Controls 0.1

FgPage {
    id: aircraftsPage

    title: qsTr("Aircrafts control")

    //    actions: [
    //        Action {
    //            iconName: "content/add"
    //            name: "Add aircraft"
    //            hoverAnimation: true
    //            enabled: true
    //            onTriggered: _manager.addAircraft()
    //        },
    //        Action {
    //            iconName: "awesome/globe"
    //            name: "Aircrafts map"
    //            hoverAnimation: true
    //            enabled: true
    //            onTriggered: pageStack.push(Qt.resolvedUrl("FgMap.qml"), { airmodel: aircraftsList.model })
    //        },
    //        Action {
    //            iconName: "action/settings"
    //            name: "Settings"
    //            hoverAnimation: true
    //            onTriggered: pageStack.push(Qt.resolvedUrl("FgSettings.qml"), { airmodel: aircraftsList.model })
    //        }
    //    ]

    menuItem: FgAircraftsSideMenu { model: fgModel}

//    header: TabBar {
//        id: headerBar
//        currentIndex: swipeView.currentIndex
//        TabButton {
//            text: qsTr("Aircrafts control")
//        }
//        TabButton {
//            text: qsTr("Instruments")
//        }
//    }

//    SwipeView {
//        id: swipeView
//        anchors.fill: parent
//        currentIndex: headerBar.currentIndex

//        FgAircraftPage { aircraft: fgap.aircraft }
        FgInstrumentsPage { anchors.fill: parent }
//    }
}
