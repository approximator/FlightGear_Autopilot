import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem

Item {

    property string currentAiPagePath;
    property alias expanderText: __expander.text
    property QtObject fgController: null

    Connections{
        target: fgController
        onAircraftConnected: addAircraft(__othersAiModel,aircraft)
        onOurAircraftConnected: addAircraft(__controlledAiModel,aircraft)
        onAircraftDisconnected: removeAircraft(__othersAiModel,aircraft)
//        onAircraftUpdateded:
    }

    ColumnLayout{
        anchors.fill: parent

        ListView {
            id: __aiView

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop

            clip: true
            boundsBehavior: Flickable.StopAtBounds
            model: __controlledAiModel
            delegate: __itemDelegate
            header: __header
        }

        Card {
            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.preferredHeight: __expander.expanded ?  units.dp(420) + __expander.height
                                                        : units.dp(86) + __expander.height

            Behavior on Layout.preferredHeight{ NumberAnimation { duration: 300; easing.type: Easing.InOutQuad } }
            SlideExpander{
                id: __expander

                text: "expander"
                height: units.dp(16)
                anchors{
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                onClicked: {
                    __aiView.headerItem.expanded = false;
                    expanded =! expanded
                }
            }
            backgroundColor: Qt.darker(Theme.backgroundColor,1.2)

            ListView {
                id: __otherView

                anchors{
                    top: __expander.bottom
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                }
                clip: true
                model: __othersAiModel
                delegate: __otherItemDelegate
                boundsBehavior: Flickable.StopAtBounds
            }

            Scrollbar {
                flickableItem: __otherView
            }

        }
    }

    Component.onCompleted: {
        __aiView.currentIndex = -1;
        __otherView.currentIndex = -1;
    }

ListModel{
    id: __controlledAiModel
}

ListModel{
    id: __othersAiModel
}

    Component {
        id: __itemDelegate
        ListItem.Standard {
            text: callsign
            interactive: true
            selected: ListView.isCurrentItem
//            onTriggered:{
//                currentAiPagePath = pagePath;
//                ListView.view.currentIndex = index;
//                ListView.view.headerItem.expanded = true;
//                __expander.expanded = false;
//                __otherView.currentIndex = -1;
//            }
        }
    }

    Component {
        id: __header
        FgInfoHeader{
            id: __headerItem

            property QtObject currentModelItem: ListView.view.model.get(ListView.view.currentIndex) || null
            imageSource: currentModelItem.imagePath
            text: currentModelItem.callsign
        }
    }

    Component {
        id: __otherItemDelegate
        ListItem.Standard {
            text: callsign
            interactive: true
            selected: ListView.isCurrentItem
//            onTriggered:{
//                __aiView.currentIndex = -1;
//                ListView.view.currentIndex = index;
//            }
        }
    }

    // adds aircraft to controlled* or otherAiModel
    function addAircraft (_model,_aircraft) {
        var modelObj = _aircraft.params;
        modelObj["callsign"] = _aircraft.callsign;

        // Got picture path by flight model
        modelObj["imagePath"] = "flight_pic/b1900d.jpg" //Fixme: get appropriate picture
        modelObj["pagePath"] = "AircraftPage.qml"; //Fixme: get appropriate page
        _model.append(modelObj);
    }

    function removeAircraft (_model,_aircraft) {
        var aiCallsigh = _aircraft.callsign;
        var i = 0;
        for (;i < _model.count; i+=1) {
            if (_model.get(i).callsign == aiCallsigh) {
                _model.remove(i);
                break;
            }
        }
    }
}
