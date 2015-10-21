import QtQuick 2.3
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem

ListItem.Standard {
    property alias label          : _label.text
    property alias value          : _textField.text
    property alias secondaryLabel : _secondaryLabel.text
    property alias labelWidth     : _label.width

    signal editFinished(string new_text)

    action: Icon {
        anchors.centerIn: parent
        name: "action/done"
        color: "green"
    }

    content: RowLayout {
        width: parent.width

        Label {
            id: _label
            style: "dialog"
            Layout.preferredWidth: Math.max(contentWidth, Units.dp(120))
            Layout.fillWidth: false
        }

        Label {
            id: _secondaryLabel
            style: "dialog"
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
