import QtQuick 2.2
import QtQuick.Layouts 1.1

Rectangle {
    id: mainRect
    width: 880
    height: 230
    color: "#2d2d2d"

    Rectangle {
        color: "black"
        width: parent.width * 0.6
        height: parent.height * 0.55
        anchors.left: mainRect.left
        anchors.leftMargin: mainRect.width * 0.1
        anchors.top: mainRect.top
        anchors.topMargin: mainRect.height * 0.1
        radius: 4
    }

    RowLayout {
        anchors.bottom: mainRect.bottom
        anchors.bottomMargin: mainRect.height * 0.1
        anchors.left: mainRect.left
        anchors.leftMargin: mainRect.width * 0.01
        width: mainRect.width

        ApButton {
            text: "AP"
        }
        ApButton {
            text: "FD"
        }
        ApButton {
            text: "HDG"
        }
        ApButton {
            text: "NAV"
        }
        ApButton {
            text: "APR"
        }
        ApButton {
            text: "REV"
        }
        ApButton {
            text: "ALT"
        }
        ApButton {
            text: "DN"
        }
    }


}

