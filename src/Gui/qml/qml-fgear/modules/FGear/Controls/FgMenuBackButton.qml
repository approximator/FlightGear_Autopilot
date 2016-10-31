/*
* Copyright © 2014-2016 Andrii Shelest. All rights reserved.
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

import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import FGear 0.1

Button {
    id: mbButtom

    property bool back: false

    property int animationDuration: 350

    property color color: Material.foreground
    readonly property real lineHeight: Math.round(AppConfig.dp(4))
    readonly property real lineSplacing: Math.round(AppConfig.dp(15))
    readonly property real contentHeight: Math.round(2 * (lineHeight + lineSplacing))
    property var linesModel: [
        {
            'angle': 45,
            'translateY': -lineSplacing
        },
        {
            'angle': 0,
            'translateY': 0
        },
        {
            'angle': -45,
            'translateY': lineSplacing
        }
    ]

    signal menuClicked()
    signal backClicked()

    flat: true
    clip: true

    Repeater{
        id: __linesRepeater
        model: linesModel
        delegate: __lineComponent
    }

    Component {
        id: __lineComponent
        Rectangle {
            id: __lineDelegate
            property alias translate: __lineTranslate

            color: mbButtom.color
            antialiasing: true

            height: mbButtom.lineHeight
            width: mbButtom.contentHeight
            radius: AppConfig.dp(1)

            anchors.centerIn: parent

            transform: __lineTranslate
            transformOrigin: Item.TopRight

            Translate { id: __lineTranslate; y: modelData.translateY }

            states: State {
                name: "back"
                when: back

                PropertyChanges {
                    target: __lineDelegate
                    rotation: modelData.angle
                    translate.y: 0
                }
            }

            transitions: Transition {
                PropertyAnimation {
                    target: __lineDelegate;
                    properties: "rotation, translate.y";
                    duration: animationDuration; easing.type: Easing.InOutQuad
                }
            }
        }
    }

    states: State {
        name: "back"
        when: back

        PropertyChanges {
            target: mbButtom; rotation: 180
        }
    }


    transitions: [
        Transition {
            RotationAnimation {
                target: mbButtom;
                direction: RotationAnimation.Clockwise;
                duration: animationDuration; easing.type: Easing.InOutQuad
            }
        }
    ]

    onClicked: {
        if (back)
            backClicked();
        else
            menuClicked();

        back = !back
    }
}
