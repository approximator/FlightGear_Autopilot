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

Item {
    id: tile

    property Item overlay: null
    property bool extended: false

    default property alias data: __content.data

    width: GridView.view.cellWidth
    height: GridView.view.cellHeight

    Pane {
        id: __content

        anchors.fill: parent
        anchors.margins: 20
    }

    states: [
        State {
            name: "extended_view"
            when: extended && (overlay != null)
            ParentChange {
                target: tile
                parent: overlay
                x: 0; y: 0
                height: parent.height
                width: parent.width
            }
            PropertyChanges { target: tile; z: 100 }
        }
    ]

    transitions: Transition {
        SequentialAnimation {
            ParentAnimation {
                NumberAnimation {
                    properties: "x, width, y, height"
                    duration: 400
                    easing.type: Easing.InOutQuad
                }
            }
            PropertyAction { target: tile; property: "z" }
        }
    }
}
