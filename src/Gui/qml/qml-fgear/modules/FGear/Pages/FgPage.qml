import QtQuick 2.7

import QtQuick.Controls 2.0

import FGear 0.1
import FGear.Controls 0.1
import FGear.Styles 0.1

Page {
    id: basePage

    objectName: "basePage"

    property FgBaseSideMenu menuItem: FgBaseSideMenu { }

    /* QTBUG-50992 see in SplashScreen.qml */
    background: FgBasePageBackground { }
}
