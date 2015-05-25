import QtQuick 2.2
import Material 0.1

Item {
    property real value: rotationTransform.angle
    property real radius: width / 2
    property int minValue: 0
    property int maxValue: 360
    property int stepSize: 10
    property alias pressed: _mouseArea.pressed

    anchors.margins: Units.dp(16)

    View {

        backgroundColor: Theme.accentColor

        elevation: _mouseArea.pressed ? 1 : 3
        anchors.fill: parent

        Rotation {
            id: rotationTransform
            origin.x: radius;
            origin.y: radius;
            angle: 0
        }
        transform: rotationTransform

        Rectangle {
            width: Units.dp(10)
            height: width
            radius: width/2
            color: Qt.darker(parent.color)
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }


        radius: parent.radius
    }
    MouseArea {
        id: _mouseArea
        anchors.fill: parent

        acceptedButtons: Qt.LeftButton | Qt.WheelFocus
        onWheel: {
            var sign = wheel.angleDelta.y / Math.abs(wheel.angleDelta.y);
            rotationTransform.angle = Math.min(Math.max(0, rotationTransform.angle + sign * stepSize), 360);
        }

        onPressed: {

            rotationTransform.angle = Qt.binding(
                        function (){
//                            if (!containsMouse) return 0;

                            var _xcat = mouseX - radius ;
                            var  _ycat = -(mouseY - radius);
                            var _angle = (Math.atan2( _xcat , _ycat ) * 180 / Math.PI) + 180;
                            return Math.round(_angle);
                        }
                        )
        }
    }

    Label {
        anchors.centerIn: parent
        text: value
    }

    function setValue (_val) {
        rotationTransform.angle = _val;
    }

}
