import QtQuick 2.2
import QtQuick.Layouts 1.1
import Material 0.1
import Material.ListItems 0.1 as ListItem

Item {

    property string currentAiPagePath;
//    property alias expanderText: __expander.text
//    property QtObject fgController: null //initialazed in FgWindow

    anchors {
        top:parent.top
        right: parent.right
        left: parent.left
    }
    height: childrenRect.height
    clip: true;

    Connections{
        target: fgController
        onAircraftConnected: addAircraft(__othersAiModel,aircraft)
        onOurAircraftConnected: addAircraft(__controlledAiModel,aircraft)
        onAircraftDisconnected: removeAircraft(__othersAiModel,aircraft)
//        onAircraftUpdateded:
    }

    ColumnLayout {
        id: __layout
        anchors {
            top:parent.top
            right: parent.right
            left: parent.left
        }

        Repeater {
            id: __aiView

            property int currentIndex: -1
            model: __controlledAiModel
            delegate: __itemDelegate
        }

        ThinDivider { Layout.preferredHeight: units.dp(5)}

        Repeater {
            id: __otherView

            property int currentIndex: -1
            model: __othersAiModel
            delegate: __otherItemDelegate
        }
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

            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.preferredHeight:  units.dp(48)
//            selected: currentIndex == index
            onClicked:{
                currentAiPagePath = pagePath;
                __otherView.currentIndex = -1;
            }
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
//            selected: currentIndex == index
            onClicked:{
                __aiView.currentIndex = -1;
//                ListView.view.currentIndex = index;
            }
        }
    }

    // adds aircraft to controlled* or otherAiModel
    function addAircraft (_model,_aircraft) {
        var modelObj = _aircraft.params;
        modelObj["callsign"] = _aircraft.callsign;

        // Got picture path by flight model
//        modelObj["imagePath"] = _aircraft.vehicleInfo.image
//        modelObj["pagePath"] = "AircraftPage.qml"; //Fixme: get appropriate page
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
