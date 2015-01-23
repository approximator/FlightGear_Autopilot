import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300

    title: "Autopilot"

    Action {
        id: quitAction
        text: "Quit"
        shortcut: "ctrl+q"
        iconSource: "../icons/svg/appbar.close.svg"
        iconName: "close"
        onTriggered: Qt.quit()
    }

    toolBar: ToolBar {
        id: mainToolBar
        width: parent.width
        RowLayout {
            anchors.fill: parent
            spacing: 0
            ToolButton { action: quitAction }
        }
    }

    ListView {
        model: aircraftsModel
        width: 150
        height: parent.height
        anchors.margins: 10

        delegate: Rectangle {
            height: 30
            gradient: Gradient {
                GradientStop { position: 0.0; color: mouseArea.containsMouse ? "orange" : "lightgreen" }
                GradientStop { position: 1.0; color: mouseArea.containsMouse ? "red" : "green" }
            }

            Behavior on gradient { ColorAnimation{ duration: 500} }

            width: parent.width
            radius: 3
            Text {
                text: modelData
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                wrapMode: Text.Wrap
                renderType: Text.NativeRendering
            }
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
            }
        }
    }

}
