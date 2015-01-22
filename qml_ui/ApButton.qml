import QtQuick 2.0

Rectangle {
    property alias text: btnText.text

    id: apButton
    width: 50
    height: 25
    radius: 4

    Text {
        id: btnText
        text: qsTr("text")
        font.pointSize: apButton.height * 0.6
        anchors.centerIn: parent
    }
}
