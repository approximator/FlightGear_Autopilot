import QtQuick 2.2

ListModel {

    ListElement {
        itemText: "AP"
        name: "autopilot_engage"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 2; rowSpan: 1
        column: 0; columnSpan: 1
        desc: "Autopilot engage/disengage"
        info: "When pushed, engages autopilot if all logic conditions are met.\n
The autopilot will engage in the basic roll (ROL) mode which functions as\n
a wing leveler and in the vertical speed (VS) hold mode.\n
The commanded vertical speed is be displayed in the upper right corner of autopilot\n
display area for three seconds after engagement or if either the UP or DN button is pressed.\n
The captured VS will be the vertical speed present at the moment of AP button press.\n
When pressed again, will disengage the autopilot."
    }

    ListElement {
        itemText: "HDG"
        name: "heading_mode"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 2; rowSpan: 1
        column: 2; columnSpan: 1
        desc: "Heading mode"
        info: "When pushed, will arm the Heading mode, which commands\n
the airplane to turn to and maintain the heading selected by the heading bug on either the DG or HSI.\n
A new heading may be selected at any time and will result in the airplane turning to the new heading.\n
Button can also be used to toggle between HDG and ROL modes."
    }

    ListElement {
        itemText: "NAV"
        name: "navigation_mode"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 2; rowSpan: 1
        column: 3; columnSpan: 1
        desc: "Navigation mode"
        info: "When pushed, will arm the navigation mode.\n
The mode provides automatic beam capture and tracking of VOR, LOC or GPS as selected\n
for presentation on the HSI or CDI. NAV mode is recommended for enroute navigation tracking.\n
NAV mode may also be used for front course LOC tracking when GS tracking is not desired."
    }

    ListElement {
        itemText: "APR"
        name: "approach_mode"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 2; rowSpan: 1
        column: 4; columnSpan: 1
        desc: "Approach mode"
        info: "When pushed, will arm the Approach mode.\n
This mode provides automatic beam capture and tracking of VOR,\n
GPS and LOC, and Glideslope (GS) on an ILS, as selected for presentation on the HSI or CDI.\n
APR mode is recommended for instrument approaches."
    }

    ListElement {
        itemText: "REV"
        name: "back_cource_mode"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 2; rowSpan: 1
        column: 5; columnSpan: 1
        desc: "Back cource approach mode"
        info: "When pushed, will arm the Back Course approach mode.\n
This mode functions similarly to the approach mode except that the autopilot\n
response to LOC signals is reversed, and GS is disabled."
    }

    ListElement {
        itemText: "ALT"
        name: "altitude_hold_mode"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 2; rowSpan: 1
        column: 6; columnSpan: 1
        desc: "Altitude hold mode"
        info: "When pushed, will select the Altitude Hold mode.\n
This mode provides tracking of the reference altitude.\n
The reference altitude is the altitude at the moment the ALT button is pressed.\n
If the ALT button is pressed with an established VS rate present, there will be altitude\n
overshoot (approximately 10% of the VS rate), with the airplane returned positively to the reference altitude."
    }

    ListElement {
        itemText: "UP"
        name: "trim_up"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 1; rowSpan: 1
        column: 7; columnSpan: 1
        desc: "Vertical trim button"
        info: "The action of these buttons is dependent upon the vertical mode present when pressed.\n
If VS mode is active, the initial button stroke will bring up the commanded vertical speed in the display.\n
Subsequent immediate button strokes will incre- ment the vertical speed commanded\n
either up or down at the rate of 100 ft/min per button press, or at the rate of approximately\n
300 ft/min per second if held continuously. If ALT mode is active, incremental button strokes will move\n
the altitude hold reference altitude either up or down at 20 feet per press, or if held continuously\n
will command the airplane up or down at the rate of 500 ft/min, synchronizing\n
the altitude hold reference to the actual airplane altitude upon button release."
    }

    ListElement {
        itemText: "DN"
        name: "trim_down"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 2; rowSpan: 1
        column: 7; columnSpan: 1
        desc: "Vertical trim button"
        info: "The action of these buttons is dependent upon the vertical mode present when pressed.\n
If VS mode is active, the initial button stroke will bring up the commanded vertical speed in the display.\n
Subsequent immediate button strokes will incre- ment the vertical speed commanded\n
either up or down at the rate of 100 ft/min per button press, or at the rate of approximately\n
300 ft/min per second if held continuously. If ALT mode is active, incremental button strokes will move\n
the altitude hold reference altitude either up or down at 20 feet per press, or if held continuously\n
will command the airplane up or down at the rate of 500 ft/min, synchronizing\n
the altitude hold reference to the actual airplane altitude upon button release."
    }

    ListElement {
        itemText: "ARM"
        name: "altitude_arm_mode"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 0; rowSpan: 1
        column: 8; columnSpan: 1
        desc: "Altitude arm mode"
        info: "When pushed will toggle altitude arming on or off. When ALT ARM is annunciated,\n
the autopilot will capture the altitude alerter displayed altitude (provided the aircraft is climbing\n
or descending in VS to the displayed altitude). When the autopilot is engaged, ALT arming is automatic\n
upon altitude alerter altitude selection via the rotary knobs. Note that the alerter functions\n
are independent of the arming process thus providing full time alerting, even when the autopilot is disengaged."
    }

    ListElement {
        itemText: "BAR0"
        name: "bar0_set"
        itemSource: "AutopilotItems/BaseButton.qml"
        row: 0; rowSpan: 1
        column: 9; columnSpan: 1
        desc: "Bar0 set button"
        info: "When pushed and released, will change the display from the altitude alerter selected\n
altitude to the baro setting display (either IN HG or HPA) for 3 seconds. If pushed and held for 2 seconds,\n
will change the baro setting display from IN HG to HPA or vice versa.\n
Once the baro setting display is visible the rotary knobs may be used to manually adjust\n
the baro setting if automatic baro correc- tion is not available."
    }

    ListElement {
        itemText: ""
        name: "display"
        itemSource: "AutopilotItems/Display.qml"
        row: 0; rowSpan: 2
        column: 1; columnSpan: 6
        desc: "Autopilot display"
        info: "TODO"
    }

    ListElement {
        itemText: ""
        name: "rotary_knobs"
        itemSource: "AutopilotItems/Dial.qml"
        row: 1; rowSpan: 2
        column: 8; columnSpan: 2
        desc: "Rotary Knobs"
        info: "Used to set the altitude alerter reference altitude;\n
or may be used immediately after pressing the BARO button, to adjust the autopilot baro\n
setting to match that of the airplane’s altimeter when manual adjustment is required.\n
(In some installations the baro setting is automatically synced to that of the altimeter.)"
    }
}
