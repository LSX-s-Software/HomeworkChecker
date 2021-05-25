import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

StackView {
    width: 1046
    height: 768
    clip: true
    id: taskPage
    initialItem: Rectangle {
        width: taskPage.width
        height: taskPage.height

        Image {
            id: addBtn
            width: 60
            height: 60
            visible: true
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            source: "images/add@2x.png"
            anchors.bottomMargin: 28
            anchors.rightMargin: 32

            MouseArea {
                id: mouseArea16
                hoverEnabled: true
                anchors.fill: parent
                onClicked:
                    taskPage.push(arrange)
            }
        }

        Text {
            id: element3
            y: 32
            width: 240
            height: 53
            text: qsTr("已布置的作业")
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 40
        }

        Rectangle {
            id: rectangle7
            width: 96
            height: 43
            color: "#ffffff"
            anchors.left: parent.left
            anchors.top: element3.bottom
            anchors.topMargin: 28
            anchors.leftMargin: 32

            Text {
                id: element4
                color: "#0098f7"
                text: qsTr("待批改")
                verticalAlignment: Text.AlignVCenter
                font.weight: Font.Medium
                font.family: "Source Han Sans CN"
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pointSize: 32
            }

            MouseArea {
                id: mouseArea4
                anchors.fill: parent
            }
        }

        Rectangle {
            id: rectangle8
            width: 160
            height: 43
            color: "#ffffff"
            anchors.left: rectangle7.right
            anchors.top: element3.bottom
            anchors.topMargin: 28
            anchors.leftMargin: 32

            Text {
                id: element5
                color: "#707070"
                text: qsTr("已完成批改")
                verticalAlignment: Text.AlignVCenter
                font.weight: Font.Medium
                font.family: "Source Han Sans CN"
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pointSize: 32
            }

            MouseArea {
                id: mouseArea5
                anchors.fill: parent
            }
        }

        Component {
            id: homeworkListItem

            Rectangle {
                width: listView.width
                height: 80
                color: "#f5f5f5"
                radius: 10
                Text {
                    id: element14
                    x: 16
                    y: 9
                    height: 37
                    text: name
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 28
                    verticalAlignment: Text.AlignVCenter
                    font.family: "Source Han Sans CN"
                }

                Text {
                    id: element15
                    x: 16
                    y: 45
                    height: 27
                    color: "#8f8f8f"
                    text: "截止于" + deadline + "·已提交 " + submitted + "·未提交 " + notSubmitted
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 20
                    verticalAlignment: Text.AlignVCenter
                    font.family: "Source Han Sans CN"
                }

                MouseArea {
                    id: mouseArea7
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        taskPage.push(info)
                    }
                }
            }

        }

        ListView {
            id: listView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: rectangle7.bottom
            anchors.bottom: parent.bottom
            clip: true
            spacing: 12
            anchors.topMargin: 24
            anchors.bottomMargin: 0
            anchors.rightMargin: 32
            anchors.leftMargin: 32
            delegate: homeworkListItem
            model: ListModel {
                ListElement {
                    name: "第六章作业"
                    deadline: "2021年6月6日"
                    submitted: 25
                    notSubmitted: 5
                }
                ListElement {
                    name: "第六章作业"
                    deadline: "2021年6月6日"
                    submitted: 25
                    notSubmitted: 5
                }
                ListElement {
                    name: "第六章作业"
                    deadline: "2021年6月6日"
                    submitted: 25
                    notSubmitted: 5
                }
            }
        }

        Component {
            id: info
            InfoOfTask {}
        }
        Component{
            id:arrange
            Arrangement{}
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
