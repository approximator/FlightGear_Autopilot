import QtQuick 2.2
import Material 0.1

Button {
  anchors.fill: parent
  elevation: checked ? 0 : 3

  checkable: true
  text: itemText

  backgroundColor: checked ? Qt.lighter(Theme.primaryDarkColor) : Theme.primaryColor
  enabled: name === "autopilot_engage" ? true : false
  onCheckedChanged: buttonChecked(name, itemText, checked)
  onEnabledChanged: {
      if (!enabled) {
          checked = false;
      }
  }
  tooltip: desc
}
