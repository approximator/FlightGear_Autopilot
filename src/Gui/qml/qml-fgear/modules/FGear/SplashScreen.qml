import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Window {
    title: "FlightGear autopilot"
    visible: true
    flags: Qt.SplashScreen

    width: 300
    height: 300

    Component.onCompleted: loader.source = Qt.resolvedUrl("FgWindow.qml")

    Rectangle {
        anchors.fill: parent
        color: "lightblue"

        Label {
            id: _label
            text: "Flightgear autopilot\nLoading..."
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
    }

    Loader {
        id: loader
        asynchronous: true
        onStatusChanged: {
            if (status == Loader.Loading)
                return

            if (loader.status == Loader.Ready)
                close()
            else
                loader.sourceComponent = message
        }
    }

    Component {
        id: message
        MessageDialog {
            visible: true
            title: "Flightgear autopilot"
            icon: StandardIcon.Critical
            text: "<b>Flightgear autopilot</b> is failed to start due to errors in the main QML file.\n
                   Please report the error following this link:
                   <a href='https://github.com/approximator/FlightGear_Autopilot/issues/new'>
                   https://github.com/approximator/FlightGear_Autopilot/issues/new</a>"
            onAccepted: Qt.quit()
        }
    }
}
