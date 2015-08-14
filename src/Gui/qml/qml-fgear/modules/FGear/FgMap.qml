import QtQuick 2.0
import Material 0.1

Page {
    property QtObject airmodel: null
    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            var radius = 3

            var aircraftsCount = airmodel.rowCount()
            for (var i = 0; i < aircraftsCount; i++)
            {
                var aircraft = airmodel.get(i)
                if (aircraft.connected)
                {
                    context.beginPath();

                    // TODO: autoscale
                    var x = aircraft.x / 50 + 56000 - 1500
                    var y = aircraft.y / 50 + 86000 - 200

                    console.log("Paint ", x, y)
                    context.arc(x, y, radius, 0, 2 * Math.PI, false);
                    context.fillStyle = 'green';
                    context.fill();
                    context.lineWidth = 2;
                    context.strokeStyle = '#003300';
                    context.stroke();
                }
            }
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
}

