/*
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 * Author: Andrii Shelest
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
