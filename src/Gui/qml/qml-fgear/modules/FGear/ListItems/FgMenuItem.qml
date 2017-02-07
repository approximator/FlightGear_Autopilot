import QtQuick 2.7
import QtQuick.Controls 2.0

import FGear 0.1
import FGear.ListItems 0.1
import FGear.Styles 0.1
import FGear.Components.Actions 0.1

MenuItem {
    id: menuItem

    /* actionName is used for search in actionsManager */
    property string actionName: "menuAction"
    readonly property FgMenuAction action: !!actionsManager
                                           ? actionsManager.getByName(actionName)
                                           : null
    property FgMenuItemStyle style: FgMenuItemStyle { }

    height: style.height
    width: style.width

    // TODO
    //    property bool infoEnabled: false
    //    property bool connected: false
    //    property bool selected: false
    //    signal fgInfoClicked()

    onTriggered: {
        ListView.view.currentIndex = ListView.view.indexAt(x, y);
        action.triggered();
    }

}
