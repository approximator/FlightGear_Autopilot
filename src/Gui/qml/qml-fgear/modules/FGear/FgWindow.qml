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

//import Qt.labs.settings 1.0

import FGear 0.1
import FGear.Controls 0.1
import FGear.Components.Views 0.1
import FGear.Models 0.1

import fgap 1.0

ApplicationWindow {
    id: fgap

    property alias fgManager: __fgManager
    property alias fgModel: __fgManager.model
    property QtObject aircraft: null


    title: AppConfig.appName

    Material.theme: AppConfig.colorType
    Material.accent: AppConfig.accent
    Material.primary: AppConfig.primary
    color: Material.background

    width: AppConfig.appWindowWidth
    height: AppConfig.appWindowHeight
    // x: AppConfig.appWindowX
    // y: AppConfig.appWindowY
    visible: true

    Component.onCompleted: {
        /* It is needed to recalculate pixelDensity */
        AppConfig.screenUpdated()
    }

    FgAircraftsManager { id: __fgManager }

    FgSplitPageView {
        id: splitPageView

        anchors.fill: parent

        splitContent: FgMainViewSideMenu {
            model: __mainViewModel
        }

        FgMainView {
            id: __mainView

            anchors.fill: parent
        }

        FgMainViewModel {
            id: __mainViewModel
        }

        Connections {
            target: __mainViewModel
            onMenuSelected: __mainView.pageStack.replace(Qt.resolvedUrl(pageSource))
        }

    }


    /* Saving settings to config file */
    //    Settings {
    //        property alias x: fgap.AppConfig.appWindowX
    //        property alias y: AppConfig.appWindowY
    //        property alias width: AppConfig.appWindowWidth
    //        property alias height: AppConfig.appWindowHeight
    //    }
}
