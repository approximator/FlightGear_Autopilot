import QtQuick 2.3
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem

ListItem.Standard {
    property string label: ""
    property int labelWidth: Units.dp(120)
    property string value: ""
    signal editFinished(string new_text)

    action: Icon {
        anchors.centerIn: parent
        name: "action/done"
        color: "green"
    }

    content: RowLayout {
        anchors.centerIn: parent
        width: parent.width

        Label {
            style: "dialog"
            text: label
            Layout.preferredWidth: labelWidth
        }
        TextField {
            id: textField
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            text: value
            onEditingFinished: {
                editFinished(text)
            }
        }
    }
}
