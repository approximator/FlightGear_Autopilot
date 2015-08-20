import QtQuick 2.0
import Material 0.1

Page {
    property QtObject airmodel: null
    property string iconName: "flight_pic/flight_orange.svg"

    title: "Air map"

    actions: [
        Action {
            iconName: "av/games"
            name: "Auto center"
            hoverAnimation: true
            enabled: true
            onTriggered: {
                canvas.centerOffsets = getCenterOffset(getAircraftsFromModel(airmodel))
                canvas.userDefinedOffsets = [0, 0]
            }
        }
    ]

    rightSidebar: PageSidebar{ /* Needed to fix icons overlay bug */}

    Canvas {
        id: canvas
        anchors.fill: parent

        property var centerOffsets: [0, 0]
        property var userDefinedOffsets: [0, 0]
        property real scale: 10000
        property int gridSize: scale / 100

        onPaint: {
            var aircrafts = getAircraftsFromModel(airmodel)
            var ctx = getContext("2d")
            var im = ctx.createImageData(iconName);

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
                var x = (aircraft.lon - centerOffsets[0]) * scale + userDefinedOffsets[0] + width / 2
                var y = (aircraft.lat - centerOffsets[1]) * scale - userDefinedOffsets[1] + height / 2

                ctx.translate(x, height - y)
                ctx.fillText(aircraft.lat.toFixed(4), 10, -10);
                ctx.fillText(aircraft.lon.toFixed(4), 10, 1);
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
            anchors {
                right: parent.right
                bottom: parent.bottom
                margins: Units.dp(32)
            }
            value: 100
            focus: true
            numericValueLabel: true
            stepSize: 1
            minimumValue: 50
            maximumValue: 200
            onValueChanged: {
                canvas.scale = value * 100
            }
        }

        Component.onCompleted: {
            centerOffsets = getCenterOffset(getAircraftsFromModel(airmodel))
            loadImage(iconName)
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
        var aircraftsCount = airmodel.rowCount()
        for (var i = 0; i < aircraftsCount; ++i) {
            var aircraft = airmodel.get(i)
            if (aircraft == null) {
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
            xSum += aircraft.lon
            ySum += aircraft.lat
        })
        return [xSum / len, ySum / len]
    }
}

