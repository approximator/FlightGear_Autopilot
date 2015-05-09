import QtQuick 2.2


Item {
    id: _pointer

    clip: true

    Component {
        id: _delegate
        IndicatorItem {
            parentIndicator: getItemByName(parentItem);
            anchors.fill: parent
        }
    }

    PictorialNavigationModel {
        id: _indicatorsModel
    }

    Repeater {
        id: _repeater
        model: _indicatorsModel
        delegate: _delegate
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
                            var _angle = (Math.atan2( _xcat , _ycat ) * 180 / Math.PI) + 360;
                            return Math.round(_angle);
                        }
                        )
        }
        onWheelScrollChanged: setHeading(wheelScroll);
    }

    function setCompass(_value) {
        getModelItemByName("compass").value = _value;
    }

    function setCourseSelect(_value) {
        getModelItemByName("couse_pointer").value = _value;
    }

    function setCourseLine(_value) {
        getModelItemByName("course_line").value = _value;
    }

    function setHeading(_value) {
        getModelItemByName("heading").value = _value;
    }

    function getModelItemByName (_name) {
        var i;
        var _item;
        for (i = 0; i < _indicatorsModel.count; i += 1) {
            _item = _indicatorsModel.get(i);
            if (_item.name == _name) {
                return _item;
            }
        }
    }
    function getItemByName (_name) {
        var i;
        var _item;
        for (i = 0; i < _indicatorsModel.count; i += 1) {
            _item = _indicatorsModel.get(i);
            if (_item.name == _name) {
                return _repeater.itemAt(i);
            }
        }
        return null;
    }
}
