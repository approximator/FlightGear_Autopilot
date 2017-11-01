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
import QtQuick.Window 2.2
import Qt.labs.settings 1.0

import FGear 0.1
import FGear.Controls 0.1
import FGear.Components.Views 0.1
import FGear.Components.Actions 0.1
import FGear.Styles 0.1

import fgap 1.0

ApplicationWindow {
    id: mainWindow
    objectName: "mainWindow"


    property FgBaseActionManager actionsManager: FgMainViewActionManager { }

    property FgAircraftsManager aircraftsManager: FgAircraftsManager { }
    property FgBaseActionManager aircraftActionManager:
        FgAircraftActionManager { aircraftObjects.model: aircraftsManager.model }

    property FgMainWindowStyle style: FgMainWindowStyle { }

    title: AppConfig.appName

    Material.theme: style.colorType
    Material.accent: style.accent
    Material.primary: style.primary

    color: style.background

    width: style.width
    height: style.height
    visible: true

    Component.onCompleted: {
        /* It is needed to recalculate pixelDensity */
        AppConfig.screenUpdated(Screen);
    }

    FgSplitPageView {
        id: splitPageView

        anchors.fill: parent

        splitContentWidth: style.sideBarWidth
        splitContent: FgMainViewSideMenu { }

        FgMainView {
            anchors.fill: parent
            menuActions: FgBaseActionGroup {
                actions: actionsManager.getActionsByName("PageMenuAction");
            }
        }

    }

    /* Saving settings to config file */
    Settings {
        category: mainWindow.objectName
        property alias x: mainWindow.x
        property alias y: mainWindow.y
        property alias width: mainWindow.width
        property alias height: mainWindow.height
    }
}
