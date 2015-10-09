import QtQuick 2.2
import Material 0.1

View {
    anchors.fill: parent
    backgroundColor: "#2e1c1c"
    elevation: 1
    Label {
        id: _label
        font.family: "Roboto"
        font.weight: Font.Bold
        font.pixelSize: Units.dp(45)
        color: itemTextColor

        anchors {
            left: parent.left
            margins: Units.dp(20)
        }
        text: itemText
    }
}
