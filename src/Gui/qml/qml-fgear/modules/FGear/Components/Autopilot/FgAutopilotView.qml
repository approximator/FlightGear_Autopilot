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

import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import FGear 0.1
import FGear.Controls 0.1
import FGear.Models 0.1

FocusScope {
    id: autopilot

    anchors.centerIn: parent
    width: AppConfig.dp(1200)
    height: AppConfig.dp(200)

    property bool engaged: false

    signal buttonChecked (string btn_name, string mode, bool checked)

    signal autopilotEngage (bool activate)
    signal modeChanged (string mode)
    signal altitudeChanged (int altitude)
    signal vesticalSpeedChanged (int vspeed)

    Rectangle {
        anchors.fill: parent
        color: "gray"
        opacity: 0.8
        radius: AppConfig.dp(5)
        border.color: Qt.darker(color)
        border.width: AppConfig.dp(3)
    }

    FgAutopilotModel { id: __autopilotModel }

    GridLayout {
        columns: 10
        rows: 3
        rowSpacing: AppConfig.dp(32)
        columnSpacing: AppConfig.dp(32)

        anchors.rightMargin: AppConfig.dp(20)
        anchors.leftMargin: AppConfig.dp(20)
        anchors.topMargin: AppConfig.dp(16)
        anchors.bottomMargin: AppConfig.dp(16)

        anchors.fill: parent

        Repeater {
            id: __buttons
            model: __autopilotModel

            Loader {
                Layout.row: row
                Layout.rowSpan: rowSpan
                Layout.column: column
                Layout.columnSpan: columnSpan
                Layout.fillHeight: true
                Layout.fillWidth: true

                asynchronous: false /* Magic artifacts if true */
                source: itemSource;
            }
        }
    }

    onEngagedChanged: {
        __buttons.itemAt(0).item.checked = engaged;
        autopilotEngage(engaged);
    }
}
