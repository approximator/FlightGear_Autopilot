import QtQuick 2.0
import Material 0.1

Page {
    property QtObject airmodel: null
    property string iconName: "flight.svg"

    title: "Air map"

    actions: [
        Action {
            name: "Zoom in"
            iconName: "content/add"
            onTriggered: {
                canvas.scale -= 1
            }
        },
        Action {
            name: "Zoom out"
            iconName: "content/remove"
            onTriggered: {
                canvas.scale += 1
            }
        }
    ]


    rightSidebar: PageSidebar{ /* Needed to fix icons overlay bug */}

    Canvas {
        id: canvas
        anchors.fill: parent

        property var centerOffsets: [0, 0]
        property real scale: 10000

        onPaint: {
            var aircrafts = getAircraftsFromModel(airmodel)
            var radius = 3

            var ctx = getContext("2d")

            ctx.fillStyle = '#aaaaaa';
            ctx.fillRect(0, 0, width, height);

            // console.log("centerOffsets[0] * scale", centerOffsets[0] * scale)
            // Draw coordinate grid
            for (var i = 0; i < width; i += 50) {
                context.beginPath();
                context.lineWidth = 0.5;
                context.moveTo(i, 0);
                context.strokeStyle = "green"
                context.lineTo(i, height);
                context.stroke();
            }

            aircrafts.forEach(function(aircraft) {
                ctx.save();

                // TODO: autoscale
                var x = (aircraft.lon - centerOffsets[0]) * scale + width / 2
                var y = (aircraft.lat - centerOffsets[1]) * scale + height / 2

                ctx.translate(x, width / 2 - y)
                ctx.rotate(aircraft.heading * Math.PI / 180.0)
                ctx.drawImage(iconName, 0, 0)

                // console.log("center ", centerOffsets[0], centerOffsets[1])
                // console.log("Paint ", aircraft.callsign, x, y)
                ctx.resetTransform()
                ctx.restore();
            })
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
        aircrafts.forEach(function(aircraft) {
            xSum += aircraft.lon
            ySum += aircraft.lat
        })
        return [xSum / len, ySum / len]
    }
}

