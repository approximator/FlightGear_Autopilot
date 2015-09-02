import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import Material 0.1
import Material.ListItems 0.1 as ListItem
import FGear.SettingsItems 0.1

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
        header: "Aircrafts"
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

            FileDialog {
                property var acceptedAction: null
                id: fileDialog
                selectFolder: true
                onAccepted: {
                    var url = fileDialog.fileUrl.toString()
                    url = Qt.platform.os == "windows" ? url.replace(
                                                             /^(file:\/{3})/,
                                                             "") : url.replace(
                                                             /^(file:\/{2})/,
                                                             "")
                    if (acceptedAction != null)
                        acceptedAction(decodeURIComponent(url))
                }
            }

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

                LabeledTextEdit {
                    label: "Flightgear:"
                    value: fgAircraft.flightgear.exeFile
                    secondaryItem: Button {
                        text: "Browse"
                        onClicked: {
                            fileDialog.acceptedAction = function(url){
                                fgAircraft.flightgear.exeFile = url
                            }

                            fileDialog.selectFolder = false
                            fileDialog.open()
                        }
                    }
                    onEditFinished: {
                        fgAircraft.flightgear.exeFile = new_text
                    }
                }

                LabeledTextEdit {
                    label: "Root dir:"
                    value: fgAircraft.flightgear.rootDir
                    secondaryItem: Button {
                        text: "Browse"
                        onClicked: {
                            fileDialog.acceptedAction = function(url){
                                fgAircraft.flightgear.rootDir = url
                            }
                            fileDialog.open()
                        }
                    }
                    onEditFinished: {
                        if(new_text.substr(-1) === '/') {
                            new_text = new_text.substr(0, new_text.length - 1);
                        }
                        fgAircraft.flightgear.rootDir = new_text
                    }
                }

                LabeledTextEdit {
                    label: "Protocol file: " + fgAircraft.flightgear.rootDir
                    labelWidth: Units.dp(500)
                    value: "/Protocol/FgaProtocol.xml"
                    secondaryItem: Button {
                        text: "Browse"
                    }
                }

                LabeledTextEdit {
                    label: "Listen port:"
                    value: fgAircraft.transport.listenPort
                    onEditFinished: {
                        fgAircraft.transport.listenPort = parseInt(new_text)
                    }
                }

                LabeledTextEdit {
                    label: "Flightgear port:"
                    value: fgAircraft.transport.port
                    onEditFinished: {
                        fgAircraft.transport.port = parseInt(new_text)
                    }
                }
            }
        }
    }
}
