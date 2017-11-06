import QtQuick 2.7

import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import FGear 0.1
import FGear.Components.Pointers 0.1

ApplicationWindow {
    width: 600
    height: contentLayout.childrenRect.height

    ColumnLayout {
        id: contentLayout

        anchors.fill: parent
        spacing: 10

        PictorialNavigation {
            id: pictorial

            Layout.preferredHeight: 600
            Layout.preferredWidth: height
        }

        Slider {
            id: compas

            Layout.fillWidth: true
            value: 30
            from: 0
            to: 360
            stepSize: 10
            onVisualPositionChanged: pictorial.setCompass(value)
        }
        Slider {
            id: course_select

            Layout.fillWidth: true
            value: 70
            from: -1000
            to: 1000
            onVisualPositionChanged: pictorial.setCourseSelect(value)
        }
        Slider {
            id: course_line

            Layout.fillWidth: true
            value: -70
            from: -1000
            to: 1000
            stepSize: 50
            onVisualPositionChanged: pictorial.setCourseLine(value)
        }
        Slider {
            id: heading

            Layout.fillWidth: true
            value: 20
            from: 0
            to: 360
            stepSize: 10
            onVisualPositionChanged: pictorial.setHeading(value)
        }
    }
}
