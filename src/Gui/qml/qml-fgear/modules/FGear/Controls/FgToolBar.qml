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

    signal settingsClicked()
    signal mapClicked()
    signal menuClicked()
    signal backClicked()

    /* QTBUG-50992 see in SplashScreen.qml */
    background: FgToolBarBackground {}

    RowLayout {
        anchors.fill: parent

        FgMenuBackButton {
//            back: drawer.visible || pageStack.depth > 1
//            onBackClicked: pageStack.pop()
//            onMenuClicked: drawer.open()

            Layout.preferredWidth: height
        }

        FgLabel {
            id: titleLabel

            styleName: "title"

            Layout.fillWidth: true
            Layout.leftMargin: AppConfig.dp(30)
            Layout.alignment: Qt.AlignVCenter
        }

        ToolButton {
            text: qsTr("\uD83C Map")
            onClicked: mapClicked()
        }

        ToolButton {
            text: qsTr("\u25C0 Settings")
            onClicked: settingsClicked()
        }
    }
}
