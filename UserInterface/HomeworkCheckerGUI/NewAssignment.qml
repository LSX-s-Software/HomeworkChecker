import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12


Rectangle {
    id: newAssignment
    width: 922
    height: 640
    radius: 20
    clip: true
    color: "#ffffff"

    Text {
        id: element
        width: 128
        height: 32
        text: qsTr("布置作业")
        verticalAlignment: Text.AlignVCenter
        font.weight: Font.Medium
        font.family: "Source Han Sans CN"
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 27
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 32
    }

    Rectangle {
        id: title
        width: 400
        height: 33
        anchors.leftMargin: 52
        anchors.top: element.bottom
        Text {
            id: element29
            width: 48
            height: 32
            text: qsTr("标题")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 0
            font.pixelSize: 24
            font.weight: Font.Medium
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
        }

        Text {
            id: element30
            x: 129
            height: 32
            text: qsTr("第七章作业")
            anchors.right: parent.right
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 24
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
        }
        anchors.left: parent.left
        anchors.topMargin: 24
    }

    Rectangle {
        id: targetClass
        width: 400
        height: 33
        anchors.top: element.bottom
        anchors.right: parent.right
        anchors.topMargin: 24
        anchors.rightMargin: 52
        Text {
            id: element31
            width: 48
            height: 32
            text: qsTr("目标班级")
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 24
            font.weight: Font.Bold
            horizontalAlignment: Text.AlignLeft
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
            font.bold: true
        }

        Text {
            id: element32
            x: 129
            height: 32
            text: qsTr("第七章作业")
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 24
            anchors.right: parent.right
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
        }
    }

    Rectangle {
        id: deadline
        width: 817
        height: 33
        anchors.top: title.bottom
        anchors.left: parent.left
        anchors.topMargin: 24
        anchors.leftMargin: 52
        Text {
            id: element33
            height: 32
            text: qsTr("截止时间")
            font.italic: false
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 24
            font.weight: Font.Medium
            horizontalAlignment: Text.AlignLeft
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
            font.bold: true
        }

        TextInput {
            id: textInput
            height: 32
            text: qsTr("2021年6月1日 23:59:59")
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }
    }

    Rectangle {
        id: describtion
        x: 52
        y: 204
        width: 818
        height: 338
        color: "#ffffff"

        Text {
            id: element1
            x: 0
            width: 96
            text: qsTr("作业描述")
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            font.weight: Font.Medium
            font.pixelSize: 24
        }

        Rectangle {
            id: rectangle2
            x: 116
            width: 702
            height: 329
            radius: 5
            clip: true

            TextArea {
                id: textArea
                text: qsTr("")
                anchors.fill: parent
                placeholderText: "输入作业描述"
                font.family: "Source Han Sans CN"
                selectByMouse: true
            }
        }
    }

    Rectangle {
        id: setBtn
        width: 218
        height: 56
        color: "#0098f7"
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32

        Text {
            id: element2
            color: "#ffffff"
            text: qsTr("创建")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }

    Image {
        id: close
        width: 32
        height: 32
        anchors.rightMargin: 20
        anchors.topMargin: 20
        anchors.right: parent.right
        MouseArea {
            id: mouseArea17
            hoverEnabled: true
            anchors.fill: parent
            onClicked: newAssignmentPopup.close()
        }
        source: "images/close.png"
        anchors.top: parent.top
    }
}










