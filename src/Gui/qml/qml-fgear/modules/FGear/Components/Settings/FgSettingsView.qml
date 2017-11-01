import QtQuick 2.7

import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import FGear 0.1
import FGear.ListItems 0.1

Flickable {
    id: settingsView

    contentWidth: parent.width
    contentHeight: childrenRect.height

    topMargin: AppConfig.dp(50)
    ScrollIndicator.vertical: ScrollIndicator { }

    //            FgAircraftsList {
    //                id: aircraftsList
    //                model: airmodel
    //                Component.onCompleted: _sidebar.contents = aircraftsList
    //            }
    Frame {
        id: settingsContent

        anchors {
            left: parent.left
            right: parent.right
            margins: AppConfig.dp(50)
        }

        ColumnLayout {
            anchors.fill: parent
            Pane {
                id: fgStatus

                background: Rectangle { color: Qt.lighter(Material.background) }

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: AppConfig.dp(16)
                }

                height: column.implicitHeight + AppConfig.dp(32)

                //                    elevation: 1
                //                    radius: AppConfig.dp(2)

                //                    FileDialog {
                //                        property var acceptedAction: null
                //                        id: fileDialog
                //                        selectFolder: true
                //                        onAccepted: {
                //                            var url = fileDialog.fileUrl.toString()
                //                            url = Qt.platform.os == "windows" ? url.replace(
                //                                                                    /^(file:\/{3})/,
                //                                                                    "") : url.replace(
                //                                                                    /^(file:\/{2})/,
                //                                                                    "")
                //                            if (acceptedAction != null)
                //                                acceptedAction(decodeURIComponent(url))
                //                        }
                //                    }

                ColumnLayout {
                    id: column

                    anchors {
                        fill: parent
                        topMargin: AppConfig.dp(16)
                        bottomMargin: AppConfig.dp(16)
                    }

                    Label {
                        id: titleLabel

                        anchors {
                            left: parent.left
                            right: parent.right
                            margins: AppConfig.dp(16)
                        }

                        //                            style: "title"
                        text: "Flightgear"
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: AppConfig.dp(8)
                    }

                    LabeledTextEdit {
                        label: "Flightgear:"
                        value: "fgAircraft.flightgear.exeFile"
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
                        value: "fgAircraft.flightgear.rootDir"
                        secondaryItem: Button {
                            text: "Browse"
                            onClicked: {
                                fileDialog.acceptedAction = function(url){
                                    fgAircraft.flightgear.rootDir = url
                                }
                                fileDialog.selectFolder = true
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
                        label: "Protocol file: "
                        secondaryLabel: "fgAircraft.flightgear.rootDir"
                        value: "/Protocol/FgaProtocol.xml"
                    }

                    LabeledTextEdit {
                        label: "Listen port:"
                        value: "fgAircraft.transport.listenPort"
                        onEditFinished: {
                            fgAircraft.transport.listenPort = parseInt(new_text)
                        }
                    }

                    LabeledTextEdit {
                        label: "Flightgear port:"
                        value: "fgAircraft.transport.port"
                        onEditFinished: {
                            fgAircraft.transport.port = parseInt(new_text)
                        }
                    }
                }
            }
        }
    }
}
