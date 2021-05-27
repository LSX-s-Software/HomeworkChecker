import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import Qt.labs.platform 1.0
import mySettingPage 1.0

Rectangle {
    id: settingPage
    width: 1046
    height: 768
    color: "#ffffff"

    MySettingPage {
        id:setting
    }

    Text {
        id: title
        x: 483
        width: 80
        height: 53
        text: qsTr("设置")
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 40
        verticalAlignment: Text.AlignVCenter
        font.family: "Source Han Sans CN"
        font.weight: Font.Medium
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 32
    }

    Rectangle {
        id: rectangle11
        width: 160
        height: 43
        color: "#ffffff"
        radius: 10
        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.leftMargin: 32
        anchors.topMargin: 28
        Text {
            id: element24
            text: "下载文件夹"
            font.weight: Font.Medium
            topPadding: -3
            font.family: "Source Han Sans CN"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 30
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouseArea11
            anchors.fill: parent
        }
    }

    Rectangle {
        id: rectangle13
        height: 80
        color: "#f5f5f5"
        radius: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: rectangle11.bottom
        anchors.rightMargin: 32
        anchors.leftMargin: 32
        anchors.topMargin: 20
        Text {
            id: element22
            x: 16
            y: 9
            width: 168
            height: 37
            text: qsTr("附件下载目录")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }

        Text {
            id: element23
            x: 16
            y: 44
            width: 166
            height: 27
            text:folderDialog.folder
            activeFocusOnTab:true
            //selectByMouse: true //是否可以选择文本
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 18
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                folderDialog.open()
            }
        }

        FolderDialog {
            id: folderDialog
            folder: "file:tmp"
            }
    }

    Rectangle {
        id: rectangle14
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10
        anchors.left: parent.left
        anchors.top: rectangle13.bottom
        anchors.leftMargin: 32
        anchors.topMargin: 16



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
            anchors{
                verticalCenter: Text.verticalCenter
                left: Text.right
                leftMargin: 20
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                setting.setWorkPath(element23.text)
            }
        }
    }

    Rectangle {
        id: rectangle15
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10
        anchors.left: rectangle14.right
        anchors.top: rectangle13.bottom
        anchors.leftMargin: 16
        anchors.topMargin: 16
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

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
