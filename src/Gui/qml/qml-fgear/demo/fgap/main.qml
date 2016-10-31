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
import QtQuick.Layouts 1.1

import FGear 0.1
import fgap 1.0

ApplicationWindow {
    id: testFgapWindow

    property alias fgapWindow: fgap_loader.item

    title: "FGap Gui Test"

    width: 320
    height: 240

    Component {
        id: fgap_window_comp
        FgWindow { }
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

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Button {
            Layout.alignment: Qt.AlignLeft
            text: "add flight"
            onClicked: fgapWindow.fgManager.addAircraft();
        }
        Button {
            Layout.alignment: Qt.AlignRight
            text: "add other flight"
            onClicked: fgapWindow.fgManager.addAircraft();
        }
    }


}
