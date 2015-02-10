import QtQuick 2.3
import Material 0.1
import Material.ListItems 0.1 as ListItem

ListItem.BaseListItem {
    id: listItem

    height: expanded ? units.dp(200) : 0

    property alias imageSource: __imageItem.source
    property alias text: label.text
    property bool expanded: false

    Behavior on height{ NumberAnimation { duration: 300; easing.type: Easing.InOutQuad } }
    Image {
        id: __imageItem

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: units.dp(1)
        }

        height: parent.height
        smooth: true
        fillMode: Image.PreserveAspectCrop
        mipmap: true
        clip: true
    }

    showDivider: false
    Label {
        id: label

        font.bold: true
        elide: Text.ElideRight
        style: "headline"
        color: "white"

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin:  units.dp(16)
    }
    IconButton{
        id: __expandButton
        anchors {
            bottom: parent.bottom
            right: parent.right
            margins: units.dp(8)
        }
        height: units.dp(26)
        width: height

        name: "navigation/expand_less"
        color: "white"
        onTriggered: expanded = false
    }
}
