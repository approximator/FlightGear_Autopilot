import QtQuick 2.7

import QtQuick.Controls 2.0

import FGear 0.1

FgPage {

    objectName: "mapPage"

    property var airmodel: []
    property string iconName: "../icons/flight/flight_orange.svg"

    title: qsTr("Air map")

    //    actions: [
    //        Action {
    //            iconName: "av/games"
    //            name: "Auto center"
    //            hoverAnimation: true
    //            enabled: true
    //            onTriggered: {
    //                canvas.centerOffsets = getCenterOffset(getAircraftsFromModel(airmodel))
    //                canvas.userDefinedOffsets = [0, 0]
    //            }
    //        }
    //    ]

    Canvas {
        id: canvas
        anchors.fill: parent

        property var centerOffsets: [0, 0]
        property var userDefinedOffsets: [0, 0]
        property real scale: scaleSlider.visualValue(100)
        property int gridSize: scale / 100

        Image {
            id: _flightImage
            source: iconName
            visible: false
        }

        onPaint: {
            var aircrafts = getAircraftsFromModel(airmodel)
            var ctx = getContext("2d")
            var im = _flightImage;

            ctx.fillStyle = '#222222';
            ctx.fillRect(0, 0, width, height)

            // Draw coordinate grid
            ctx.beginPath()
            ctx.lineWidth = 0.8
            ctx.fillStyle = "yellow";
            var x = userDefinedOffsets[0] % gridSize
            var y = userDefinedOffsets[1] % gridSize
            for (; x < width; x += gridSize) {
                ctx.moveTo(x, 0)
                ctx.lineTo(x, height)
                var txtX = centerOffsets[0] + (x - userDefinedOffsets[0] - width / 2) / scale
                if (gridSize > 70 || Math.floor(x / gridSize) % 2 == 0) {
                    ctx.fillText(txtX.toFixed(4), x - 10, 15);
                }
            }
            for (; y < height; y += gridSize) {
                ctx.moveTo(0, y)
                ctx.lineTo(width, y)
                var txtY = centerOffsets[1] + (height - (y - userDefinedOffsets[1]) - height / 2) / scale
                ctx.fillText(txtY.toFixed(4), 5, y);
            }
            ctx.strokeStyle = "green"
            ctx.stroke()

            aircrafts.forEach(function(aircraft) {
                ctx.save()

                // TODO: autoscale
                var x = (aircraft.longitude - centerOffsets[0]) * scale + userDefinedOffsets[0] + width / 2
                var y = (aircraft.latitude - centerOffsets[1]) * scale - userDefinedOffsets[1] + height / 2

                ctx.translate(x, height - y)
                ctx.fillText(aircraft.latitude.toFixed(4), 10, -10);
                ctx.fillText(aircraft.longitude.toFixed(4), 10, 1);
                ctx.rotate(aircraft.heading * Math.PI / 180.0)
                ctx.drawImage(im, -im.width/2, -im.height/2)

                // console.log("center ", centerOffsets[0], centerOffsets[1])
                // console.log("Paint ", aircraft.callsign, x, y)
                ctx.resetTransform()
                ctx.restore();
            })
        }

        MouseArea {
            property int prevX: 0
            property int prevY: 0
            property int prevXOffset: 0
            property int prevYOffset: 0

            anchors.fill: parent
            hoverEnabled: false

            onPressed: {
                prevX = mouse.x
                prevY = mouse.y
                prevXOffset = canvas.userDefinedOffsets[0]
                prevYOffset = canvas.userDefinedOffsets[1]
            }

            onPositionChanged: {
                canvas.userDefinedOffsets[0] = prevXOffset + mouse.x - prevX
                canvas.userDefinedOffsets[1] = prevYOffset + mouse.y - prevY
                canvas.requestPaint();
            }
        }

        Slider {
            id: scaleSlider

            readonly property int defaultValue: 100

            anchors {
                right: parent.right
                bottom: parent.bottom
                margins: AppConfig.dp(32)
            }

            from: 50.0
            to: 200.0
            stepSize: 1.0
            value: defaultValue

            snapMode: Slider.SnapOnRelease

            function visualValue (_scale) {
                var mappedValue = (visualPosition * to) + from;

                if (typeof _scale !== "indefined")
                    mappedValue *= _scale;

                return mappedValue;
            }
        }

        Component.onCompleted: {
            centerOffsets = getCenterOffset(getAircraftsFromModel(airmodel))
        }
    }
    Timer {
        id: timer;
        interval: 100;
        running: true;
        repeat: true
        onTriggered: {
            canvas.requestPaint();
        }
    }

    function getAircraftsFromModel(model) {
        var aircrafts = []
        var aircraftsCount = 0;/*airmodel.rowCount()*/
        for (var i = 0; i < aircraftsCount; ++i) {
            var aircraft = airmodel.get(i)
            if (aircraft === null) {
                console.error('aircraft is null')
                continue
            }

            if (aircraft.connected){
                aircrafts.push(aircraft)
            }
        }
        return aircrafts
    }

    function getCenterOffset(aircrafts) {
        var xSum = 0
        var ySum = 0
        var len = aircrafts.length
        if (len < 1) {
            return [0, 0]
        }
        aircrafts.forEach(function(aircraft) {
            xSum += aircraft.longitude
            ySum += aircraft.latitude
        })
        return [xSum / len, ySum / len]
    }
}
