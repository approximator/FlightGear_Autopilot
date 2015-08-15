import QtQuick 2.0
import Material 0.1

Page {
    property QtObject airmodel: null

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

    Canvas {
        id: canvas
        anchors.fill: parent

        property var centerOffsets: [0, 0]
        property int scale: 10

        onPaint: {
            var aircrafts = getAircraftsFromModel(airmodel)

            var ctx = getContext("2d")
            var radius = 3

            aircrafts.forEach(function(aircraft) {
                ctx.save();
                // ctx.clearRect(0, 0, width, height);

                // TODO: autoscale
                var x = (aircraft.x - centerOffsets[0]) / scale + width / 2
                var y = (aircraft.y - centerOffsets[1]) / scale + height / 2

                // console.log("center ", centerOffsets[0], centerOffsets[1])
                // console.log("Paint ", aircraft.callsign, x, y)

                ctx.beginPath();
                ctx.arc(x, y, radius, 0, 2 * Math.PI, false);
                ctx.fillStyle = 'green';
                ctx.fill();
                ctx.lineWidth = 2;
                ctx.strokeStyle = '#003300';
                ctx.stroke();
                ctx.restore();
            })
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
            xSum += aircraft.x
            ySum += aircraft.y
        })
        return [xSum / len, ySum / len]
    }
}

