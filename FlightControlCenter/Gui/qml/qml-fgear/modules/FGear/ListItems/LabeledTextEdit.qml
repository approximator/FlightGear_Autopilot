import QtQuick 2.7

import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import FGear 0.1
import FGear.Controls 0.1

ItemDelegate {
    property alias label          : _label.text
    property alias value          : _textField.text
    property alias secondaryLabel : _secondaryLabel.text
    property alias labelWidth     : _label.width

    signal editFinished(string new_text)

//    action: Icon {
//        anchors.centerIn: parent
//        name: "action/done"
//        color: "green"
//    }

    RowLayout {
        width: parent.width

        Label {
            id: _label
            Layout.preferredWidth: Math.max(contentWidth, AppConfig.dp(120))
            Layout.fillWidth: false
        }

        Label {
            id: _secondaryLabel
            Layout.preferredWidth: contentWidth
            Layout.fillWidth: false
        }

        TextField {
            id: _textField
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            onEditingFinished: {
                editFinished(text)
            }
        }
    }
}
