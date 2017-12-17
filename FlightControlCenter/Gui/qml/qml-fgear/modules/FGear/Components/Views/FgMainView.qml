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

import FGear.Controls 0.1
import FGear.Pages 0.1
import FGear.Styles 0.1
import FGear.Components.Actions 0.1

FgPage {
    id: mainView

    property FgMenuActionGroup menuActions

    readonly property string initialActionName: "aircraftsPageMenuAction"
    readonly property string pagesDirPrefix: "../../";

    /* QTBUG-50992 see in SplashScreen.qml */
    background: FgMainViewBackground { }

    StackView {
        id: __pageStack

        property bool pushFirst: true

        function openPage(source) {
            var url = Qt.resolvedUrl(source);
            console.info("[MainView] Open page ", url);

            if (pushFirst) {
                pushFirst = false;
                __pageStack.push(url);
            } else {
                __pageStack.replace(url);
            }

        }

        anchors.fill: parent
        initialItem: FgBusyPage { }
    }

    header: FgToolBar { title: __pageStack.currentItem.title }
    footer: FgAircraftsStatusBar {}

    Connections {
        target: menuActions.activatedAction
        onMenuSelected: __pageStack.openPage(pagesDirPrefix + source)
    }

    Component.onCompleted: {
        activateInitialAction();
    }

    function activateInitialAction() {
        var initial = null;
        var i = 0;
        for (; i < menuActions.actions.length; i++) {
            if(menuActions.actions[i].objectName === initialActionName) {
                initial = menuActions.actions[i];
                break;
            }
        }

        if (initial !== null) {
            initial.triggered();
        } else {
            console.error("[MainView] Can not found action", initialActionName);
        }
    }
}
