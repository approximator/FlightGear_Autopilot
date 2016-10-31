import QtQuick 2.7
import QtQuick.Controls 2.0

import FGear 0.1
import FGear.Components.Pointers 0.1

FgPage {
    title: qsTr("Instruments")

    PictorialNavigation {
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height)
        height: width
        heading: 0

        states: State {
            name: "active"
            when: fgap.aircraft
            PropertyChanges { heading: fgap.aircraft.heading}
        }
    }
}
