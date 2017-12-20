import QtQuick 2.7
import QtQuick.Controls 2.3

import FGear 0.1
import FGear.ListItems 0.1
import FGear.Styles 0.1
import FGear.Components.Actions 0.1

Button {
    id: menuItem

    property FgMenuItemStyle style: FgMenuItemStyle { }

    action: modelData
    text: action ? action.text : ""

    height: style.height
    width: style.width
    display: AbstractButton.TextOnly

    flat: true
}
