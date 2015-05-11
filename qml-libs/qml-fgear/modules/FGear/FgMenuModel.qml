import QtQuick 2.0

ListModel {

    ListElement {
        menuSection: "Aircrafts"
        name: "MyApp"
        menuIcon: "maps/flight"
        status: "connected"
        pagePath: "FgAircraftPage.qml"
        connected: true
    }
    ListElement {
        menuSection: "Aircrafts"
        name: "MyApp2"
        menuIcon: "maps/flight"
        status: "disconnected"
        pagePath: "FgAircraftPage.qml"
        connected: false
    }

    ListElement {
        menuSection: "Other Aircrafts"
        name: "otherVasia"
        menuIcon: "maps/flight"
        status: "connected"
        pagePath: "FgAircraftPage.qml"
        connected: true
    }
    ListElement {
        menuSection: "FlightGear Setings"
        name: "Flight Gear settings"
        menuIcon: "notification/folder_special"
        status: "connected"
        pagePath: "SettingsPage.qml"
        connected: false
    }
}
