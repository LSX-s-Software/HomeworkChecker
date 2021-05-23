import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
    Rectangle {
        id: rectangle
        width: 1046
        height: 768
        color: "#ffffff"



        //Component
        Component{
            id: homeworkListItem
Rectangle {
    id: rectangle1


    x: 32
    y: 248
    width: 983
    height: 61
    color: "#f5f5f5"

    Text {
        id: numberOfHomework
        text: "第"+number+"章作业"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 0
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 28
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Text {
        id: scoreOfStudent
        x: 938
        y: 17
        width: 45
        text: score
        anchors.right: parent.right
        anchors.rightMargin: 45
        horizontalAlignment: Text.AlignLeft

        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 28
    }

    Image {
        id: image
        x: 974
        y: 17
        width: 9
        height: 28
        anchors.rightMargin: 20
        anchors.right: parent.right
        fillMode: Image.PreserveAspectFit
        source: "images/more.png"
    }
}
 }

        //endcompoennt
        Rectangle {
            id: backBtn
            x: -4
            y: 3
            width: 76
            height: 28
            color: "#ffffff"
            anchors.leftMargin: 28
            anchors.topMargin: 46
            anchors.left: parent.left
            Text {
                id: element3
                color: "#0098f7"
                text: qsTr("返回")
                font.pixelSize: 28
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

            MouseArea {
                id: mouseArea1
                anchors.fill: parent
            }

            Image {
                id: image1
                width: 25
                height: 22
                source: "images/backBtn.png"
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
            }
            anchors.top: parent.top
        }

        Text {
            id: element
            height: 40
            text: qsTr("李四的各次成绩")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 40
        }

        ListView {
            id: listView
            x: 0
            width: 982
            height: 487
            anchors.top: parent.top
            anchors.topMargin: 120
            anchors.horizontalCenter: parent.horizontalCenter
            delegate: homeworkListItem
            model: ListModel {
                ListElement {
                    number:"一"
                    score:"89"
                }

                ListElement {
                    number:"二"
                    score:"89"
                }

                ListElement {
                    number:"三"
                    score:"89"
                }

                ListElement {
                    number:"四"
                    score:"89"
                }
            }

        }
    }


