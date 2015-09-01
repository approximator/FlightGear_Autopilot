import QtQuick 2.2
import Material 0.1

Button {
  anchors.fill: parent
  elevation: checked ? 1 : 2

  checkable: true
  text: itemText

  backgroundColor: Qt.lighter(Theme.primaryDarkColor)
  enabled: name === "autopilot_engage" ? true : (engaged)
  onCheckedChanged: buttonChecked(name, itemText, checked)
  tooltip: desc
}
