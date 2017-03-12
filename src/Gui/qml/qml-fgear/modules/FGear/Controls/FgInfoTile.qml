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

FgTile {
    id: infoTile
    objectName: "infoTile"

    overlay: tileView.overlayItem

    RowLayout {
        anchors.fill: parent
        anchors.margins: 5

        Rectangle {
            id: image

            Layout.preferredHeight: parent.height
            Layout.preferredWidth: height

            color: connected ? "green" : "lightgrey"
        }

        Column {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Label {
                id: callsignLabel

                width: parent.width
                text: callsign
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }


            Label {
                width: parent.width
                text: "Connected: " + connected
            }

            Button {
                text: "run flightGear"
                onClicked: qtObject.runFlightGear()
            }
            Button {
                text: infoTile.extended ? "less Info" : "more Info"
                onClicked: infoTile.extended = !infoTile.extended
            }
        }

    }

}
