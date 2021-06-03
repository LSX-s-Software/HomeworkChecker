import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import HomeworkVC 1.0

Rectangle {
    id: markHomework
    x: 0
    y: 0
    width: 1046
    height: 768
    color: "#ffffff"
    radius: 10
    Rectangle {
        id: homeworkOfStudents
        y: 203
        width: 748
        height: 540
        color: "#ffffff"
        radius: 1
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter
        TextArea {
                    id: textArea
                    text: correctHomework.contentText
                    anchors.fill: parent
                    font.weight: Font.Medium
                    font.family: "Source Han Sans CN"
                    font.pixelSize: 20
                }
        anchors.left: parent.left
        border.width: 1
    }

    Text {
        id: element1
        width: 160
        height: 40
        text: qsTr("批改作业")
        font.weight: Font.Medium
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        anchors.topMargin: 40
        font.pixelSize: 40
    }

    Rectangle {
        id: backBtn
        width: 76
        height: 28
        color: "#ffffff"
        anchors.leftMargin: 28
        anchors.top: parent.top
        Text {
            id: element2
            color: "#0098f7"
            text: qsTr("返回")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked:
                taskPage.pop()
        }

        Image {
            id: image
            width: 25
            height: 22
            source: "images/backBtn.png"
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: parent.verticalCenter
        }
        anchors.left: parent.left
        anchors.topMargin: 46
    }

    Text {
            id: element3
            x: 808
            y: 114
            width: 56
            height: 28
            text: qsTr("附件")
            font.bold: false
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 28
        }

        ListView {
                id: listView
                x: 0
                y: 148
                height: 506
                //width: 982
                //height: 456
                clip: true
                spacing: 8
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: classHere.bottom
                anchors.topMargin: 24
                anchors.rightMargin: 40
                anchors.leftMargin: 794
                anchors.bottomMargin: 114
                anchors.bottom: parent.bottom
                delegate: attachmentListItem
                model: attachmentModel
            }

       /*
        Rectangle {
            id: addition
            x: 808
            y: 163
            width: 198
            height: 70
            color: "#f5f5f5"
            radius: 10

            Text {
                id: element4
                text: qsTr("6-28.cpp")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                anchors.fill: parent
                font.pixelSize: 28
            }

            MouseArea {
                id: mouseArea1
                anchors.fill: parent
                onClicked:
                    taskPage.push(detailOfAddition)
            }
        }
        */
        //ComponentBegein
           Component{

               id: attachmentListItem
               Rectangle {
                   id: rectangle1
                   //x: 808
                   //y: 163
                   width: 198
                   height: 50
                   color: "#f5f5f5"
                   radius: 10

                   Text {
                       id: element4
                       text: fileName
                       verticalAlignment: Text.AlignVCenter
                       anchors.fill: parent
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.left: parent.left
                       anchors.leftMargin: 8
                       font.bold: false
                       font.family: "Source Han Sans CN"
                       font.pixelSize: 20
                   }

                   MouseArea {
                       id: mouseArea1
                       anchors.fill: parent
                   }
               }

           }
           //endComponent

    Rectangle {
        id: markBtn
        x: 788
        y: 676
        width: 218
        height: 56
        color: "#0098f7"
        radius: 10
        Text {
            id: element7
            color: "#ffffff"
            text: qsTr("打分")
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            font.weight: Font.Medium
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea4
            anchors.fill: parent
            onClicked:
            {
                correctHomework.comment=textField.text
                correctHomework.score=textField1.text
                correctHomework.submit()
            }
        }
    }

    Rectangle {
        id: comment
        x: 40
        y: 680
        width: 541
        height: 48
        color: "#f5f5f5"

        MouseArea {
            id: mouseArea2
            anchors.fill: parent
        }

        TextField {
            id: textField
            text: qsTr("")
            font.pixelSize: 28
            anchors.fill: parent
            placeholderText: "评语"
        }
    }

    Rectangle {
        id: score
        x: 597
        y: 680
        width: 175
        height: 48
        color: "#f5f5f5"

        MouseArea {
            id: mouseArea3
            anchors.fill: parent
        }

        TextField {
            id: textField1
            text: qsTr("100")
            font.weight: Font.Medium
            placeholderText: ""
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
        }
    }
    border.color: "#00000000"
    border.width: 1
}










/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
