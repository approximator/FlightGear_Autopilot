import QtQuick 2.7

import QtQuick.Controls 2.0

import FGear 0.1
import FGear.Styles 0.1

Page {
    id: baseSideMenuPage
    objectName: "baseEmptySideMenu" // Should be overrided in children items

    property FgSideMenuStyle style: FgSideMenuStyle { }

    /* QTBUG-50992 see in SplashScreen.qml */
    background: FgBaseSideMenuBackground { }
}
