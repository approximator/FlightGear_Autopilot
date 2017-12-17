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

pragma Singleton

QtObject {
    id: appConfig

    readonly property string appName: qsTr("Flight Gear Autopilot")
    property bool showSplashScreen: true
    property bool showSidebar: true

    /* Pixel density dependent helpers */
    readonly property real defaultPixelDensity: 4.46
    property real pixelDensity: defaultPixelDensity
    property real multiplier: 1.4

    Binding on pixelDensity { id: pdBinding }
    onPixelDensityChanged: {
        console.log("[AppConfig] pixelDensity updated to: ", pixelDensity);
    }
    function screenUpdated(screen) {
        pdBinding.when = typeof screen === "object";

        if (pdBinding.when)
            pdBinding.value = screen.pixelDensity
    }

    function dp(number) {
        return Math.round(number*((pixelDensity*25.4)/160)*multiplier);
    }

}
