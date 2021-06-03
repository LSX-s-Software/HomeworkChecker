import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import StudentScoreVC 1.0

Rectangle {
    id: rectangle
    width: 1046
    height: 768
    color: "#ffffff"

    property string stuName: "加载中"
    property int stuId: -1
    property int classId: -1

    StudentScoreVC {
        id: studentScoreVC
    }

    ListModel {
        id: homeworkListModel
    }

    function loadData() {
        studentScoreVC.loadData(stuId, classId)
        homeworkListModel.clear()
        studentScoreVC.scoreList.forEach(ele => {
                                      homeworkListModel.append(ele)
                                  })
    }

    //Component
    Component{
        id: homeworkListItem
        Rectangle {
            id: rectangle1
            width: listView.width
            height: 61
            color: "#f5f5f5"

            Text {
                id: numberOfHomework
                text: name
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
                anchors.rightMargin: 20
                horizontalAlignment: Text.AlignRight
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 28
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
        anchors.verticalCenter: element.verticalCenter
        anchors.leftMargin: 28
        anchors.left: parent.left
        Text {
            id: element3
            color: "#0098f7"
            text: qsTr("返回")
            font.weight: Font.Medium
            font.pixelSize: 28
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            anchors.fill: parent
            horizontalAlignment: Text.AlignRight
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: {
                stuName = "加载中"
                stuId = -1
                classId = -1
                markPage.pop()
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
    }

    Text {
        id: element
        height: 40
        text: stuName + "的各次成绩"
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
        model: homeworkListModel
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
