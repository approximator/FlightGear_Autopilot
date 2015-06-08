import QtQuick 2.3
import FGear 0.1
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Dialogs 1.0


Page {
    id: page
    title: "Settings"

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        selectFolder: true
        visible: false
        onRejected: {
            console.log("Canceled")
            visible: false
        }
    }

    ColumnLayout {
        anchors {
            fill: parent
            topMargin: Units.dp(16)
            bottomMargin: Units.dp(16)
        }

        View {
            id: fgStatus

            anchors {
                left: parent.left
                right: parent.right
                margins: Units.dp(16)
            }

            height: column.implicitHeight + Units.dp(32)

            elevation: 1
            radius: Units.dp(2)

            ColumnLayout {
                id: column

                anchors {
                    fill: parent
                    topMargin: Units.dp(16)
                    bottomMargin: Units.dp(16)
                }

                Label {
                    id: titleLabel

                    anchors {
                        left: parent.left
                        right: parent.right
                        margins: Units.dp(16)
                    }

                    style: "title"
                    text: "Flightgear"
                }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: Units.dp(8)
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
                            Layout.preferredWidth: Units.dp(100)
                        }
                        TextField {
                            id: executableField
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignVCenter
                            text: "/usr/games/fgfs"
                        }
                        Button {
                            Layout.alignment: Qt.AlignVCenter
                            text: "Browse"
                            textColor: Theme.primaryColor
                            onClicked: {
                                fileDialog.setSelectFolder(false)
                                fileDialog.title = "Select Flightgear executable"
                                fileDialog.accepted.connect(function() {
                                    executableField.text = decodeURIComponent(fileDialog.fileUrl.toString().replace("file://",""))
                                    fileDialog.destroy()
                                })
                                fileDialog.open()
                            }
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
                            Layout.preferredWidth: Units.dp(100)
                        }
                        TextField {
                            id: dataField
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignVCenter
                            text: "/usr/share/games/flightgear/"
                        }
                        Button {
                            Layout.alignment: Qt.AlignVCenter
                            text: "Browse"
                            textColor: Theme.primaryColor
                            onClicked: {
                                fileDialog.setSelectFolder(true)
                                fileDialog.title = "Select Flightgear data directory"
                                fileDialog.accepted.connect(function() {
                                    dataField.text = decodeURIComponent(fileDialog.fileUrl.toString().replace("file://",""))
                                    fileDialog.destroy()
                                })
                                fileDialog.open()
                            }
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
                            Layout.preferredWidth: Units.dp(100)
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
                margins: Units.dp(16)
            }

            height: column2.implicitHeight + Units.dp(32)

            elevation: 1
            radius: Units.dp(2)

            ColumnLayout {
                id: column2

                anchors {
                    fill: parent
                    topMargin: Units.dp(16)
                    bottomMargin: Units.dp(16)
                }

                Label {
                    id: titleLabel2

                    anchors {
                        left: parent.left
                        right: parent.right
                        margins: Units.dp(16)
                    }

                    style: "title"
                    text: "Other settings"
                }
            }
        }
    }

}
