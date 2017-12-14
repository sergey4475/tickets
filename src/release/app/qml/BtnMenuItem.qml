import QtQuick 2.9

Item {
    id: root
    width: 48
    height: 48
    property string textItem: ""
    property string fileicon: ""

    Rectangle {
        id: rectangle
        width: 48
        height: 48
        color: "#00000000"
        radius: 12
        border.width: 0

        Text {
            id: text1
            text: qsTr(textItem)
            opacity: 0
            font.pixelSize: 12
            visible: false

        }

        Image {
            id: image
            width: 48
            height: 48
            fillMode: Image.PreserveAspectCrop
            source: fileicon
        }

        MouseArea {
            id: mouseArea
            x: 0
            y: 0
            width: 48
            height: 48
            hoverEnabled: true
            anchors.fill: parent
            onEntered:  {
                rectangle.color = "#1c4169"

            }
            onExited:  { rectangle.color = "#00000000"}

        }


    }

    state: "menu"
    states: [
        State {
            name: "menu"
            PropertyChanges {
                target: text1
                visible: false
            }
        },
        State {
            name: "back"

            PropertyChanges {
                target: root
                width: 200
            }

            PropertyChanges {
                target: mouseArea
                width: 200
                clip: false
                opacity: 1
            }

            PropertyChanges {
                target: text1
                x: 49
                y: 0
                width: 151
                height: 48
                color: "#ffffff"
                text: "Главная"
                leftPadding: 5
                font.letterSpacing: 0
                font.wordSpacing: 0
                font.pixelSize: 12
                visible: true
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                opacity: 1
            }

            PropertyChanges {
                target: rectangle
                width: 200
                radius: 12
                border.color: "#d1e726"
                border.width: 0
                scale: 1
                clip: false
            }
        }
    ]

}
