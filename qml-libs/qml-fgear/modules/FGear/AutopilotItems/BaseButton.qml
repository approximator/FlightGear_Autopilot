import QtQuick 2.2
import Material 0.1

Button {
  anchors.fill: parent
  elevation: checked ? 1 : 2
  backgroundColor: elevation > 1 ? "white" : "darkgrey"
  checkable: true
  text: itemText
  enabled: true;
  onCheckedChanged: console.log(checked)
  tooltip: desc
}
