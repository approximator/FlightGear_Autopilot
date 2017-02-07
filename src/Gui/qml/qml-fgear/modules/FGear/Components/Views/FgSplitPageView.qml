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

import QtQuick.Layouts 1.1

import FGear 0.1
import FGear.Components.Actions 0.1

Item {
    id: splitPageView

    property string actionName: "menuShowAction"
    readonly property FgSideBarShowAction action: !!actionsManager
                                               ? actionsManager.getByName(actionName)
                                               : null

    property int splitContentWidth: 200
    property bool sidePanelHidden: action ? !action.isShown : false

    default property alias data: baseContent.data
    property alias splitContent: splitContent.data

    RowLayout {
        id: layout

        anchors.fill: parent
        spacing: 0.0

        Item {
            id: splitContent

            Layout.preferredWidth: splitContentWidth
            Layout.fillHeight: true

            clip: true
        }

        Item {
            id: baseContent

            Layout.fillHeight: true
            Layout.fillWidth: true

            clip: true
        }
    }

    states: [
        State {
            name: "hide_left_side"
            when: sidePanelHidden
            PropertyChanges { target: splitContent; Layout.preferredWidth: 0; }
        }
    ]

    transitions: [
        Transition {
            from: "*"
            to: "hide_left_side"
            SequentialAnimation {
                NumberAnimation { targets: splitContent; properties: "Layout.preferredWidth"; duration: 400 }
                PropertyAction { target: splitContent; property: "visible"; value: false }
            }
        },
        Transition {
            from: "hide_left_side"
            to: "*"
            SequentialAnimation {
                PropertyAction { target: splitContent; property: "visible"; value: true }
                NumberAnimation { target: splitContent; properties: "Layout.preferredWidth"; duration: 400 }
            }
        }
    ]
}
