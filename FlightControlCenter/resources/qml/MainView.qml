import QtQuick 2.0
import FGear 0.1

SplashScreen {
    id: splash

    windowSource: "FgWindow.qml"

    /* QTBUG-50992 set to true after fix */
    asynchronous: false
}
