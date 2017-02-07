import QtQuick 2.7

import QtQuick.Controls 2.0

import FGear 0.1

FgBaseSideMenu {
    id: listSideMenu
    objectName: "listSideMenu"

    property alias delegate: menuList.delegate
    property alias model: menuList.model

    anchors.fill: parent

    header: Label {
        text: title

        font.pointSize: 14

        horizontalAlignment: Text.AlignHCenter
        topPadding: style.topPadding
        bottomPadding: style.bottomPadding
    }

    FgList {
        id: menuList

        anchors.fill: parent
    }
}
