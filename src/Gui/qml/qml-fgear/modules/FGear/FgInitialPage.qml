import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

Page {
    id: page

    property QtObject aircraftsModel;
    property variant sections: ["Aircrafts"]
    property var fgAircraft: null

    title: "Aircrafts control"

    actions: [
        Action {
            iconName: "action/settings"
            name: "Settings"
            hoverAnimation: true
        },

        Action {
            iconName: "alert/warning"
            name: "THIS SHOULD BE HIDDEN!"
            visible: false
        }
    ]

    TabView {
        id: tabView
        anchors.fill: parent
        currentIndex: page.selectedTab
        model: sections

        delegate: Item {
            width: tabView.width
            height: tabView.height

            property alias sidebarView: _sidebar
            clip: true

            /*Right side menu*/
            Sidebar {
                id: _sidebar
                expanded: true
                autoFlick: false

                ListView {
                    id: menuList
                    height: childrenRect.height
                    anchors {
                        left: parent.left
                        right: parent.right
                        top: parent.top
                    }

                    model: aircraftsModel
                    clip: true

                    delegate: FgMenuItem {
                        selected: ListView.isCurrentItem
                        onClicked: {
                            menuList.currentIndex = index;
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

                FgAircraftPage {
                    anchors {
                        top: parent.top
                        bottom: parent.bottom
                        right: parent.right
                        left: _sidebar.right
                    }

                    aircraft: fgAircraft
                }
            }
        }
    }
