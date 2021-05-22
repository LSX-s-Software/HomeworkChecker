import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Rectangle {
    id: rectangle
    x: 0
    y: 0
    width: 1046
    height: 768
    color: "#ffffff"

        Text {
            id: element
            x: 308
            y: 70
            text: qsTr("第六章作业")
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 40
        }

        ListView {
            id: listView
            spacing: 0
            clip: true
            anchors.right: parent.right
            anchors.rightMargin: 32
            anchors.left: parent.left
            anchors.leftMargin: 32
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 140
            anchors.top: parent.top
            anchors.topMargin: 172
            model: ListModel {
                ListElement {
                    name: "第六章作业"
                    colorCode: "grey"
                    deadline:""
                    submitted:1
                    notSubmmitted:1
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    spacing: 10
                }
            }
        }
}


