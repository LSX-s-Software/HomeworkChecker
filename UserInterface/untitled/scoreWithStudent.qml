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
            width: 983
            height: 61
            color: "#f5f5f5"

            Text {
                id: numberOfHomework
                text: "第"+number+"章作业"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 16
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 28
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
            }

            Text {
                id: scoreOfStudent
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
                width: 9
                height: 28
                anchors.rightMargin: 20
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
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
            onClicked:
                markPage.pop()
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
        verticalAlignment: Text.AlignVCenter
        font.family: "Source Han Sans CN"
        font.weight: Font.Medium
        font.bold: false
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40
    }

    ListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: element.bottom
        anchors.bottom: parent.bottom
        anchors.rightMargin: 32
        anchors.leftMargin: 32
        anchors.bottomMargin: 0
        clip: true
        anchors.topMargin: 40
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



/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:12}
}
##^##*/
