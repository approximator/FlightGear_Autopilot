import QtQuick 2.2
import Material 0.1

Button {
  anchors.fill: parent
  elevation: checked ? 1 : 2
  backgroundColor: elevation > 1 ? "white" : "darkgrey"
  checkable: autopilotItem.checkable
  text: autopilotItem.data
  enabled: true;
  onCheckedChanged: console.log(checked)
}
