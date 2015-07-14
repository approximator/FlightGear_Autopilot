import QtQuick 2.4
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import FGear 0.1

Window {
    width: 600
    height: 800

    ColumnLayout {
        anchors.fill: parent
        spacing: 20

        PictorialNavigation {
            id: pictorial
            Layout.preferredHeight: 600
            Layout.preferredWidth: height
        }

        Row {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter

            spacing: 10
            SpinBox {
                id: compas
                value: 30
                minimumValue: 0
                maximumValue: 360
                onValueChanged: pictorial.setCompass(value)
            }
            SpinBox {
                id: course_select
                value: 70
                minimumValue: -1000
                maximumValue: 1000
                onValueChanged: pictorial.setCourseSelect(value)
            }
            SpinBox {
                id: course_line
                value: -70
                minimumValue: -1000
                maximumValue: 1000
                onValueChanged: pictorial.setCourseLine(value)
            }
            SpinBox {
                id: heading
                value: 20
                minimumValue: 0
                maximumValue: 360
                onValueChanged: pictorial.setHeading(value)
            }
        }
    }
}
