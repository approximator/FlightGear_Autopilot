import QtQuick 2.3
import FGear 0.1
import QtQuick 2.0
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem

Page {
    id: page
    title: "Settings"

    ColumnLayout {
        anchors {
            fill: parent
            topMargin: units.dp(16)
            bottomMargin: units.dp(16)
        }

        View {
            id: fgStatus

            anchors {
                left: parent.left
                right: parent.right
                margins: units.dp(16)
            }

            height: column.implicitHeight + units.dp(32)

            elevation: 1
            radius: units.dp(2)

            ColumnLayout {
                id: column

                anchors {
                    fill: parent
                    topMargin: units.dp(16)
                    bottomMargin: units.dp(16)
                }

                Label {
                    id: titleLabel

                    anchors {
                        left: parent.left
                        right: parent.right
                        margins: units.dp(16)
                    }

                    style: "title"
                    text: "Flightgear"
                }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: units.dp(8)
                }

                ListItem.Standard {
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
                            text: "Executable:"
                            Layout.preferredWidth: units.dp(100)
                        }
                        TextField {
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignVCenter
                            text: "/usr/games/fgfs"
                        }
                        Button {
                            Layout.alignment: Qt.AlignVCenter
                            text: "Browse"
                            textColor: Theme.primaryColor
                        }
                    }
                }

                ListItem.Standard {
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
                            text: "Data dir:"
                            Layout.preferredWidth: units.dp(100)
                        }
                        TextField {
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignVCenter
                            text: "/usr/share/games/flightgear/"
                        }
                        Button {
                            Layout.alignment: Qt.AlignVCenter
                            text: "Browse"
                            textColor: Theme.primaryColor
                        }
                    }
                }

                ListItem.Standard {
                    action: Icon {
                        anchors.centerIn: parent
                        name: "alert/warning"
                        color: "red"
                    }

                    content: RowLayout {
                        anchors.centerIn: parent
                        width: parent.width

                        Label {
                            style: "dialog"
                            text: "Protocol file:"
                            Layout.preferredWidth: units.dp(100)
                        }
                        TextField {
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignVCenter
                            text: "/usr/share/games/flightgear/Protocol/FgaProtocol.xml"
                        }
                        Button {
                            Layout.alignment: Qt.AlignVCenter
                            text: "Write"
                            textColor: Theme.primaryColor
                        }
                    }
                }

                ListItem.Standard {
                    action: Item { }

                    content: Button {
                            Layout.alignment: Qt.AlignVCenter
                            text: "Run"
                            textColor: Theme.primaryColor
                    }
                }

            }
        }



        View {
            anchors {
                left: parent.left
                right: parent.right
                margins: units.dp(16)
            }

            height: column2.implicitHeight + units.dp(32)

            elevation: 1
            radius: units.dp(2)

            ColumnLayout {
                id: column2

                anchors {
                    fill: parent
                    topMargin: units.dp(16)
                    bottomMargin: units.dp(16)
                }

                Label {
                    id: titleLabel2

                    anchors {
                        left: parent.left
                        right: parent.right
                        margins: units.dp(16)
                    }

                    style: "title"
                    text: "Other settings"
                }
            }
        }
    }

}
