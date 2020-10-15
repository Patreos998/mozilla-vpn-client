/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

import QtQuick 2.5
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../themes/themes.js" as Theme

RoundButton {
    id: button

    height: 40
    width: Theme.maxTextWidth
    anchors.horizontalCenter: parent.horizontalCenter

    Layout.preferredHeight: 40
    Layout.fillWidth: true

    Layout.leftMargin: 16
    Layout.rightMargin: 16

    VPNFocus {
        itemToFocus: button
        anchors.margins: -4
        radius: 6
        focusWidth: 5
    }

    background: Rectangle {
        id: bgColor
        color: Theme.blueButton.defaultColor
        radius: 4

        Behavior on color {
            ColorAnimation {
                duration: 200
            }
        }
    }

    Keys.onReturnPressed: clicked()
    Accessible.onPressAction: clicked()

    contentItem: Label {
        id: label
        color: "#FFFFFF"
        text: button.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        font.family: Theme.fontBoldFamily
        font.pixelSize: 15
    }


    state: "state-default"
    states: [
        State {
            name: "state-default"
            PropertyChanges {
                target: bgColor
                color: Theme.blueButton.defaultColor
            }
        },
        State {
            name: "state-hovering"
            PropertyChanges {
                target: bgColor
                color: Theme.blueButton.buttonHovered
            }
        },
        State {
            name: "state-pressed"
            PropertyChanges {
                target: bgColor
                color: Theme.blueButton.buttonPressed
            }
        }

    ]

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: button.state = "state-hovering"
        onExited: button.state = "state-default"
        onPressed: button.state = "state-pressed"
        onClicked: button.clicked();
    }
}
