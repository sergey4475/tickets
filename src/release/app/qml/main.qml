import QtQuick 2.9
import QtQuick.Controls 2.2


Item {
    property alias mouseArea: mouseArea
    property int animationDuration: 350

    Rectangle {
        id: main
        x: 0
        y: 0
        width: 48
        height: parent.height
        color: "#ffffff"
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#3271b0"
            }

            GradientStop {
                position: 0.994
                color: "#26598f"
            }
        }
        state: "back"

        MenuBackButton{
            id: menuBackButton
            x: 12
            y: 3
            state: "back"
            //anchors.centerIn: parent
        }

        MouseArea {
            id: mouseArea
            x: 12
            y: 3
            width: 24
            height: 24
            anchors.rightMargin: 8
            anchors.bottomMargin: 453
            anchors.leftMargin: 12
            anchors.topMargin: 8
            //anchors.fill: menuBackButton
            onClicked: {
                menuBackButton.state = menuBackButton.state === "menu" ? "back":"menu"
                main.state = main.state === "menu" ? "back":"menu"
                btnMenuItem.state = btnMenuItem.state === "menu" ? "back":"menu"
            }
        }

        BtnMenuItem {
            id: btnMenuItem
            x: 0
            y: 56
            fileicon: qsTr("qrc:/main/list.png")
            antialiasing: true
            textItem: "Справочники"
            state: "back"
        }


        transitions: [
            Transition {
                RotationAnimation {target: main; direction: RotationAnimation.Clockwise; duration: animationDuration; easing.type: Easing.InOutQuad }
            }
        ]

        states: [
            State {
                name: "menu"
            },
            State {
                name: "back"

                PropertyChanges {
                    target: main
                    width: 200

                }


                PropertyChanges {
                    target: mouseArea
                    x: 166
                }

            }
        ]
    }

    BtnMenuItem {
        id: btnMenuItem1
        x: 0
        y: 111
    }
}
