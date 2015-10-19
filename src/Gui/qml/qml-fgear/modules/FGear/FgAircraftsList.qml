import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

ListView {
    width: parent.width
    height: childrenRect.height
    highlight: Item {
        Rectangle {
            color: theme.accentColor
            opacity: 0.7
            width: Units.dp(6)
            anchors {
                top: parent.top
                bottom: parent.bottom
                left: parent.left
                topMargin: Units.dp(10)
                bottomMargin: Units.dp(10)
                leftMargin: Units.dp(2)
            }
        }
    }

    clip: true
    highlightFollowsCurrentItem: true
    boundsBehavior: Flickable.StopAtBounds

    delegate: _listComponent

    Component {
        id: _listComponent
        FgMenuItem {
            selected: ListView.isCurrentItem
            infoEnabled: ListView.isCurrentItem
            onFgInfoClicked: fgAircraft.runFlightGear()
            onClicked: {
                ListView.view.currentIndex = index;
                fgAircraft = aircraft;
            }

            Component.onCompleted: {
                if (index === 0) {
                    fgAircraft = aircraft;
                }
            }
        }
    }
}
