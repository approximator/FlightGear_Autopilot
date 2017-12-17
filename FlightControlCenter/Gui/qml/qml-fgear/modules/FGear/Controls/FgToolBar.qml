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
import QtQuick.Layouts 1.3

import FGear 0.1
import FGear.Styles 0.1

ToolBar {
    id: toolBar

    property alias title: titleLabel.text

    /* QTBUG-50992 see in SplashScreen.qml */
    background: FgToolBarBackground {}
    padding: 5

    RowLayout {
        anchors.fill: parent

        FgToolBarMenuButton {
            Layout.preferredWidth: height
        }

        Label {
            id: titleLabel

            font.pointSize: 18

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
        }

        FgToolBarButton {
            actionName: "aircraftControlPageMenuAction"
            text: qsTr("\u25C0 Aircraft")
        }

        FgToolBarButton {
            actionName: "mapPageMenuAction"
            text: qsTr("\uD83C Map")
        }

        FgToolBarButton {
            actionName: "instrumentsPageMenuAction"
            text: qsTr("\u25C0 Instruments")
        }
    }
}
