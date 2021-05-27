import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    id: infoOfTask
    width: 1046
    height: 768
    color: "#ffffff"

    //ComponentBegein
    Component{

        id: studentListItem
        Rectangle {
            id: rectangle1
            x: 32
            y: 248
            width: 983
            height: 61
            color: "#f5f5f5"
            Text {
                id: nameAndNumber
                text: name+"("+number+")"
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
                hoverEnabled: true
                onClicked:
                    taskPage.push(correctHomework)

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
    //endComponent

    Text {
        id: element
        x: 308
        y: 70
        text: qsTr("第六章作业")
        font.weight: Font.Medium
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 40
    }

    ListView {
        id: listView
        x: 0
        y: 0
        width: 982
        height: 456
        clip: true
        anchors.bottomMargin: 140
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        delegate: studentListItem
        model: ListModel {
            ListElement {
                name: "李四"
                number:"2020302111000"
                score: "90"
            }
            ListElement {
                name: "李四"
                number:"2020302111000"
                score: "90"
            }
            ListElement {
                name: "李四"
                number:"2020302111000"
                score: "90"
            }
            ListElement {
                name: "李四"
                number: "2020302111000"
                score: "90"
            }
            ListElement {
                name: "李四"
                number:"2020302111000"
                score: "90"
            }
            ListElement {
                name: "李四"
                number:"2020302111000"
                score: "90"
            }
            ListElement {
                name: "李四"
                number:"2020302111000"
                score: "90"
            }
        }
    }

    Rectangle {
        id:classHere
        x: 32
        y: 120
        width: 322
        height: 28
        anchors.leftMargin: 52
        anchors.topMargin: 24
        anchors.left: parent.left
        Text {
            id: element29
            width: 48
            height: 32
            text: qsTr("班级")
            anchors.leftMargin: 0
            font.bold: false
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
            font.weight: Font.Medium
        }

        Text {
            id: element30
            x: 129
            height: 32
            text: qsTr("2020级计卓")
            font.family: "Source Han Sans CN"
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
            anchors.top: parent.top
        }
       // anchors.top: element28.bottom
    }

    ProgressBar {
        id: progressBar
        width: 982
        height: 24
        value: 0.5
        anchors.bottomMargin: 96
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: deleteTheTask
        x: 265
        y: 692
        width: 218
        height: 56
        color: "#fa5151"
        radius: 10

        Text {
            id: element1
            color: "#ffffff"
            text: qsTr("删除")
            font.weight: Font.Medium
            font.bold: false
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea2
            anchors.fill: parent
        }
    }

    Rectangle {
        id: deadLine
        x: 562
        y: 120
        width: 452
        height: 28
        anchors.topMargin: 24
        Text {
            id: element31
            width: 48
            height: 32
            text: qsTr("截止时间")
            anchors.leftMargin: 0
            font.bold: false
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 24
            font.weight: Font.Medium
        }

        Text {
            id: element32
            x: 129
            height: 32
            text: qsTr("2021年5月15日 23:59:59")
            anchors.right: parent.right
            font.family: "Source Han Sans CN"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 24
            anchors.top: parent.top
        }
       // anchors.top: element28.bottom
    }

    Rectangle {
        id: continueCorrect
        x: 563
        y: 692
        width: 218
        height: 56
        color: "#0098f7"
        radius: 10
        Text {
            id: element2
            color: "#ffffff"
            text: "继续批改"
            font.weight: Font.Medium
            font.pixelSize: 24
            font.bold: false
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            id: mouseArea3
            anchors.fill: parent
        }
    }

    Rectangle {
        id: backBtn
        x: -4
        y: 3
        width: 76
        height: 28
        color: "#ffffff"
        anchors.topMargin: 46
        anchors.leftMargin: 28
        anchors.left: parent.left
        Text {
            id: element3
            color: "#0098f7"
            text: qsTr("返回")
            font.weight: Font.Medium
            font.pixelSize: 28
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            horizontalAlignment: Text.AlignRight
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: {
                taskPage.pop()
            }
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

    Component
    {
        id:correctHomework
        CorrectHomework{}
    }



}
