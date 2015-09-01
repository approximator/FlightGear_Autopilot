import QtQuick 2.3
import fgap 1.0
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Dialogs 1.0


Page {
    id: page
    title: "Settings"
    backgroundColor: Theme.primaryDarkColor

    property alias airmodel: aircraftsList.model
    property QtObject fgAircraft: null
    onFgAircraftChanged: {
        if (fgAircraft)
            title = fgAircraft.callsign + " - settings"
    }

    FgAircraftsList {
        id: aircraftsList
    }

    /*Left side menu*/
    Sidebar {
        id: _sidebar
        header: "Aircrafts menu"
        width: Units.dp(350)
        backgroundColor: Qt.lighter(Theme.primaryDarkColor)
        contents: aircraftsList
        style: "dark"
    }

    ColumnLayout {
        anchors {
            left: _sidebar.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        View {
            id: fgStatus
            backgroundColor: Qt.lighter(Theme.primaryDarkColor)

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

//        View {
//            anchors {
//                left: parent.left
//                right: parent.right
//                margins: Units.dp(16)
//            }

//            height: column2.implicitHeight + Units.dp(32)

//            elevation: 1
//            radius: Units.dp(2)

//            ColumnLayout {
//                id: column2

//                anchors {
//                    fill: parent
//                    topMargin: Units.dp(16)
//                    bottomMargin: Units.dp(16)
//                }

//                Label {
//                    id: titleLabel2

//                    anchors {
//                        left: parent.left
//                        right: parent.right
//                        margins: Units.dp(16)
//                    }

//                    style: "title"
//                    text: "Other settings"
//                }
//            }
//        }
    }

}
