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

import FGear 0.1

Drawer {
    id: sliderView

    default property alias content: menuContent.data

    property bool floating: false
    property Item splittedPage: null
    property Item splittedParent: null

    Item {
        id: menuContent

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        states: State {
            name: "split"
//            when: splittedParent && splittedPage && !floating
            PropertyChanges { target: splittedPage; anchors.fill: undefined }
            ParentChange { target: menuContent; parent: splittedParent }
            AnchorChanges {
                target: menuContent;
                anchors.right: splittedPage.left
                anchors.top: splittedPage.top
                anchors.bottom: splittedPage.bottom
            }
            AnchorChanges {
                target: splittedPage;
                anchors.left: menuContent.right
            }
        }

    }

}
