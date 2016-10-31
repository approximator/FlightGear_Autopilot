import QtQuick 2.7

import QtQuick.Controls 2.0

import FGear 0.1
import FGear.ListItems 0.1
import FGear.Components.Settings 0.1

Page {
    id: settingsPage

    property QtObject fgAircraft: null
    property var menuData: {
        'title': title,
        'model': fgap.fgModel,
        'delegate': __listComponent
    }

    title: qsTr("Settings")

    BusyIndicator {
        id: __progress

        anchors.centerIn: parent
        visible: true
    }

    Loader {
        id: __loader

        anchors.fill: parent

        asynchronous: true
        sourceComponent: settingsComponent
        onLoaded: __progress.visible = false
    }

    Component {
        id: settingsComponent

        FgSettingsView {
            id: settingsView
        }
    }

    Component {
        id: __listComponent

        FgMenuItem {
            selected: ListView.isCurrentItem
            infoEnabled: ListView.isCurrentItem
            onFgInfoClicked: fgAircraft.runFlightGear()

            connected: connected
            text: callsign

            onClicked: {
                ListView.view.currentIndex = index;
                fgAircraft = model.qtObject;
            }

            Component.onCompleted: {
                if (index === 0) {
                    fgAircraft = model.qtObject;
                }
            }
        }
    }

    states: State {
        name: "aircraftSelected"
        when: fgAircraft !== null

        PropertyChanges {
            target: settingsPage
            title: fgAircraft.callsign + " - settings"
        }
    }

}
