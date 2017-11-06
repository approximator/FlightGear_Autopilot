import QtQuick 2.7

import FGear 0.1

Item {
    id: pictorialNavigation

    property real heading: 0
    property real headingSelect: 0
    // TODO: make properties for all parameters

    property var itemsMap

    onHeadingChanged: {
        setCompass(heading)
    }

    width: AppConfig.dp(200)
    height: width

    clip: true

    Component {
        id: _delegate
        IndicatorItem {
            id: __indicator

            anchors.fill: parent

            Binding {
                when: (typeof pictorialNavigation.itemsMap === "array") && parentItem
                target: __indicator
                property: "parentIndicator"
                value: _repeater.itemAt(itemsMap[parentItem])
            }
        }
    }

    PictorialNavigationModel {
        id: _indicatorsModel
    }

    Repeater {
        id: _repeater
        model: _indicatorsModel
        delegate: _delegate

        onItemAdded: {
            var itemModel = model.get(index);
            console.log("[PictorialNavigation] New indicator: ", itemModel.name)

            if (typeof itemsMap === "undefined")
                itemsMap = {};

            itemsMap[itemModel.name] = index;

            console.log("[PictorialNavigation] " +
                        itemModel.name + "indicator added.")
        }
    }


    Image {
        id: outer_box
        anchors.fill: parent
        source: "pictorial_navigation_indicator/5_outer_box.png"
    }


    MouseArea {
        id: _mouseArea
        anchors.fill: parent
        property real wheelScroll: 0
        onWheel: {
            var sign = wheel.angleDelta.y / Math.abs(wheel.angleDelta.y);
            wheelScroll += 10 * sign;
        }

        onPressed: {
            wheelScroll = Qt.binding(
                        function (){
                            var _xcat = mouseX - width/2 ;
                            var  _ycat = -(mouseY - width/2);
                            var _angle = (Math.atan2( _xcat , _ycat ) * 180 / Math.PI);
                            //console.log(_angle)
                            return _angle;
                        }
                        )
        }
        onWheelScrollChanged: setHeading(wheelScroll);

    }

    function setCompass(_value) {
        _indicatorsModel.get(itemsMap.compass).value = _value;
    }

    function setCourseSelect(_value) {
        _indicatorsModel.get(itemsMap.couse_pointer).value = _value;
    }

    function setCourseLine(_value) {
        _indicatorsModel.get(itemsMap.course_line).value = _value;
    }

    function setHeading(_value) {
        _indicatorsModel.get(itemsMap.heading).value = _value;
    }
}
