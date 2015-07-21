import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

Page {
    id: page

    property QtObject aircraftsModel;
    property string selectedComponent: aircraftsModel.get(0)
    property var sections: ["Aircrafts"]

    title: "Aircrafts control"

    tabs: navDrawer.enabled ? [] : sections

    actionBar.maxActionCount: navDrawer.enabled ? 3 : 4

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

    backAction: navDrawer.action

    ListView {
        id: menuList

        property bool onDrawer: parent === navDrawer.drawerView
        property string currentTab: onDrawer ? "" : sections[page.selectedTab]

        anchors.fill: parent
        parent: (navDrawer && navDrawer.enabled) ?
                    navDrawer.drawerView : tabView.currentItem.sidebarView

        model: aircraftsModel
        clip: true

        delegate: FgMenuItem {
//            visible: {
//                if (menuList.onDrawer) {
//                    return true;
//                } else {
//                    return (menuSection == menuList.currentTab);
//                }
//            }

            selected: ListView.isCurrentItem
//            onClicked: {
//                reloadPage(pagePath);

//                if (menuList.onDrawer) {
//                    navDrawer.close();
//                }

//                menuList.currentIndex = index;
//            }
        }
    }
//        section {
//            property: onDrawer ? "menuSection" : ""
//            criteria: ViewSection.FullString
//            delegate: ListItem.Subheader {
//                text: section
//            }
//        }


    NavigationDrawer {
        id: navDrawer

        property alias drawerView: drawerFlickable

        enabled: page.width < Units.dp(500)

        Flickable {
            id: drawerFlickable
            anchors.fill: parent

            contentHeight: Math.max(menuList.implicitHeight, height)
        }
    }

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

            Sidebar {
                id: _sidebar
                expanded: !navDrawer.enabled
            }

            Flickable {
                id: flickable
                anchors {
                    left: _sidebar.right
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                clip: true
                contentHeight: Math.max(itemLoader.implicitHeight + 40, height)
                Loader {
                    id: itemLoader
                    anchors.fill: parent

                    asynchronous: true
                    // selectedComponent will always be valid, as it defaults to the first component
                    source: Qt.resolvedUrl(page.selectedComponent)
                }
            }
            Scrollbar {
                flickableItem: flickable
            }
        }
    }

//    function getModelSections (propertyName) {
//        var i;
//        var _sections = {};
//        var _itemSection;

//        if (aircraftsModel === undefined) {
//            return ([]);
//        }

//        for (i = 0; i < aircraftsModel.count; i+=1) {
//            _itemSection = aircraftsModel.get(i)[propertyName];

//            if (_itemSection in _sections) {
//                continue;
//            }
//            _sections[_itemSection] = true;
//        }
//        return (Object.keys(_sections));
//    }
//    function reloadPage (_pagePath) {
//        selectedComponent = ""; // It is for page reloading
//        selectedComponent = _pagePath;
//    }
}
