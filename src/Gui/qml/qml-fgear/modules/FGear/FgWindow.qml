import QtQuick 2.2
import Material 0.1

ApplicationWindow {
    id: fgap

    visible: true
    title: "Flight Gear Autopilot"

    width: 1280
    height: 720


    theme {
        primaryColor: Palette.colors["blue"]["500"]
        primaryDarkColor: Palette.colors["blue"]["700"]
        accentColor: Palette.colors["teal"]["500"]
        tabHighlightColor: "white"
    }

    property QtObject fgController: null
    Connections{
        target: fgController
        onAircraftConnected: addAircraft(aircraft, false)
        onOurAircraftConnected: addAircraft(aircraft, true)
        onAircraftDisconnected: removeAircraft(aircraft)
        onAircraftUpdated: updateAircraft(aircraft)
    }

    FgMenuModel {
        id: menuModel
    }

    FgInitialPage {
        id: startpage
        menuModel: menuModel
    }

    initialPage: startpage

    // adds aircraft to controlled* or otherAiModel
    function addAircraft (_aircraft, _our) {
        var modelObj = _aircraft.params;
        modelObj["menuSection"] = _our ? "Aircrafts" : "Other Aircrafts";
        modelObj["name"] = _aircraft.callsign;
        modelObj["connected"] = _aircraft.connected;
        modelObj["pagePath"] = "FgAircraftPage.qml"; //Fixme: get appropriate page
        modelObj["menuIcon"]  = "maps/flight";
        menuModel.append(modelObj);
    }

    function updateAircraft(_aircraft) {
        var aiCallsign = _aircraft.callsign;
        var i = 0;
        for (; i < menuModel.count; i += 1) {
            var aircraft = menuModel.get(i)
            if (aircraft.name === aiCallsign) {
                aircraft.connected = true;  // FIXME: use params object
                break;
            }
        }
    }

    function removeAircraft (aircraft) {
        var aiCallsign = _aircraft.callsign;
        var i = 0;
        for (;i < menuModel.count; i+=1) {
            if (menuModel.get(i).name === aiCallsign) {
                menuModel.remove(i);
                break;
            }
        }
    }
}
