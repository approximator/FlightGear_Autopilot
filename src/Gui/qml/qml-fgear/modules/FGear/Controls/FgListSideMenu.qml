import QtQuick 2.7

import QtQuick.Controls 2.0

import FGear 0.1

FgBaseSideMenu {
    id: listSideMenu

    objectName: "listSideMenu"

    property alias delegate: menuList.delegate
    property alias model: menuList.model

    anchors.fill: parent

    header: FgLabel {
        styleName: "headline"
        text: title

        horizontalAlignment: Text.AlignHCenter
        topPadding: AppConfig.dp(12)
        bottomPadding: AppConfig.dp(12)
    }

    FgList {
        id: menuList

        anchors.fill: parent
    }

}
