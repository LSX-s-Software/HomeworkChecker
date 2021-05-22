import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    id: settingPage
    width: 1046
    height: 768
    color: "#ffffff"
    Text {
        id: element21
        x: 483
        y: 32
        width: 80
        height: 53
        text: qsTr("设置")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 40
        verticalAlignment: Text.AlignVCenter
    }

    Rectangle {
        id: rectangle11
        x: 32
        y: 113
        width: 160
        height: 43
        color: "#ffffff"
        radius: 10
        Text {
            id: element24
            text: "下载文件夹"
            topPadding: -3
            font.family: "Source Han Sans CN"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 32
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouseArea11
            anchors.fill: parent
        }
    }

    Rectangle {
        id: rectangle13
        x: 32
        y: 176
        width: 982
        height: 80
        color: "#f5f5f5"
        radius: 10
        Text {
            id: element22
            x: 16
            y: 9
            width: 168
            height: 37
            text: qsTr("附件下载目录")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 28
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }

        Text {
            id: element23
            x: 16
            y: 44
            width: 166
            height: 27
            text: qsTr("D:\\Download\\CPP")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 20
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }

        MouseArea {
            id: mouseArea13
            anchors.fill: parent
        }
    }

    Rectangle {
        id: rectangle14
        x: 32
        y: 272
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10

        Text {
            id: element26
            color: "#0098f7"
            text: qsTr("修改")
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pointSize: 24
        }

        MouseArea {
            id: mouseArea14
            anchors.fill: parent
        }
    }

    Rectangle {
        id: rectangle15
        x: 266
        y: 272
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10
        Text {
            id: element27
            color: "#fa5151"
            text: qsTr("清空")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 24
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            font.family: "Source Han Sans CN"
        }

        MouseArea {
            id: mouseArea15
            anchors.fill: parent
        }
    }
}
