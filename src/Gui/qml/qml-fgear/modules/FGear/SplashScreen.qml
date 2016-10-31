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
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2

import FGear 0.1
import FGear.Controls 0.1

ApplicationWindow {
    id: splashWindow

    property var windowSource

    title: AppConfig.appName
    color: "transparent"

    Material.theme: AppConfig.colorType
    Material.accent: AppConfig.accent
    Material.primary: AppConfig.primary

    visible: true
    flags: Qt.SplashScreen

    width: AppConfig.splashWidth
    height: AppConfig.splashHeight

    Component.onCompleted: {

        AppConfig.screenUpdated();

        /* We need to start loading application window
         * only after splashWindow has been created */
        if (!setWindowSource(windowSource)) {
            console.error("[SplashScreen] window source didn't set.");
            loader.sourceComponent = message;
        }

    }

    function setWindowSource (_windowSource) {
        var windowSourceType = typeof _windowSource;
        switch (windowSourceType) {
            case "string":
                loader.source = Qt.resolvedUrl(_windowSource);
                return true;
            case "object":
                loader.sourceComponent = windowSource;
                return true;
            default: return false;
        }
    }

    background: Rectangle {
        radius: AppConfig.dp(10)
        color: Material.background
        opacity: 0.8
    }


    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
    }

    header: FgLabel {
        text: AppConfig.appName

        horizontalAlignment: Text.AlignHCenter
        topPadding: AppConfig.dp(3)

        font.bold: true
        styleName: "title"
    }
    footer: FgLabel {
        text: qsTr("Loading...")

        padding: AppConfig.dp(10)
        styleName: "dialog"
    }

    Loader {
        id: loader
        asynchronous: false /* QTBUG-50992 set to true after fix */
        onStatusChanged: {
            if (status == Loader.Loading)
                return

            if (loader.status == Loader.Ready)
                close()
            else
                loader.sourceComponent = message
        }
    }

    Component {
        id: message
        MessageDialog {
            visible: true
            title: AppConfig.appName
            icon: StandardIcon.Critical
            text: "<b>Flightgear autopilot</b> is failed to start due to errors in the main QML file.\n
                   Please report the error following this link:
                   <a href='https://github.com/approximator/FlightGear_Autopilot/issues/new'>
                   https://github.com/approximator/FlightGear_Autopilot/issues/new</a>"
            onAccepted: Qt.quit()
        }
    }
}
