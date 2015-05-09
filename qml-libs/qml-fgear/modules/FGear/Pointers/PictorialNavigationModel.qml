import QtQuick 2.2
import FGear 0.1

ListModel {

    ListElement {
        name: "compass"
        value: 0
        imageSource: "pictorial_navigation_indicator/1_compass.png"
        indicatorType: "circular"
        animation: true
    }

    ListElement {
        name: "couse_pointer"
        value: 0
        imageSource: "pictorial_navigation_indicator/2_course_select_pointer.png"
        indicatorType: "circular"
        animation: true
    }

    ListElement {
        name: "course_line"
        parentItem: "couse_pointer"
        value: 100
        minValue: -100
        maxValue: 100
        imageSource: "pictorial_navigation_indicator/3_course_select_pointer_line.png"
        indicatorType: "linear"
        animation: true
    }

    ListElement {
        name: "heading"
        value: 0
        imageSource: "pictorial_navigation_indicator/4_heading_select_bug.png"
        indicatorType: "circular"
        animation: true
    }

}
