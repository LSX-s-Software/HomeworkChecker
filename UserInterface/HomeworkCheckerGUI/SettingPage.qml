import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import Qt.labs.platform 1.0
import MySettingPage 1.0

Rectangle {
    id: settingPage
    width: 1046
    height: 768
    color: "#ffffff"

    MySettingPage
    {
        id:sp
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
        id: rectangleDownload
        width: 160
        height: 43
        color: "#ffffff"
        radius: 10
        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.leftMargin: 32
        anchors.topMargin: 28
        Text {
            id: textDownload
            text: "下载文件夹"
            font.weight: Font.Medium
            topPadding: -3
            font.family: "Source Han Sans CN"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHLeft
            font.pixelSize: 30
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouseAreaDownload
            anchors.fill: parent
        }
    }

    Rectangle {
        id: rectangleDownloadFolder
        height: 80
        color: "#f5f5f5"
        radius: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: rectangleDownload.bottom
        anchors.rightMargin: 32
        anchors.leftMargin: 32
        anchors.topMargin: 20
        Text {
            id: textDownloadFolder
            x: 16
            y: 9
            width: 168
            height: 37
            text: qsTr("附件下载目录")
            horizontalAlignment: Text.AlignHLeft
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }

        Text {
            id: textFolderPath
            x: 16
            y: 44
            width: 166
            height: 27
            text:folderDialog.folder
            activeFocusOnTab:true
            //selectByMouse: true //是否可以选择文本
            horizontalAlignment: Text.AlignHLeft
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
            folder: sp.getWorkPath()
            }
    }

    Rectangle {
        id: rectangleServer
        width: 160
        height: 43
        color: "#ffffff"
        radius: 10
        anchors.left: parent.left
        anchors.top: rectangleDownloadFolder.bottom
        anchors.leftMargin: 32
        anchors.topMargin: 28
        Text {
            id: textServer
            text: "服务器设置"
            font.weight: Font.Medium
            topPadding: -3
            font.family: "Source Han Sans CN"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHLeft
            font.pixelSize: 30
            verticalAlignment: Text.AlignVCenter
        }
    }

    Rectangle {
        id: rectangleServerSetting
        height: 80
        color: "#f5f5f5"
        radius: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: rectangleServer.bottom
        anchors.rightMargin: 32
        anchors.leftMargin: 32
        anchors.topMargin: 20

        Text {
            id: serverText
            x: 16
            y: 9
            width: 168
            height: 37
            text: qsTr("Websocket服务器地址")
            horizontalAlignment: Text.AlignHLeft
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }

        TextInput {
            id: serverURL
            x: 16
            y: 44
            width: 166
            height: 27
            text:sp.getWsClientUrl()
            activeFocusOnTab:true
            selectByMouse: true //是否可以选择文本
            focus:true
            horizontalAlignment: Text.AlignHLeft
            font.pixelSize: 18
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }
    }

    Rectangle {
        id: rectangleConfirm
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10
        anchors.left: parent.left
        anchors.top: rectangleServerSetting.bottom
        anchors.leftMargin: 32
        anchors.topMargin: 16



        Text {
            id: textConfirm
            color: "#0098f7"
            text: qsTr("保存")
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
                //console.log("123444")
                sp.setWorkPath(textFolderPath.text)
                sp.setWsClientUrl(serverURL.text)
                sp.saveToFile()
            }
        }
    }

    Rectangle {
        id: rectangleCancel
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10
        anchors.left: rectangleConfirm.right
        anchors.top: rectangleServerSetting.bottom
        anchors.leftMargin: 16
        anchors.topMargin: 16
        Text {
            id: textCancel
            color: "#fa5151"
            text: qsTr("取消")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 24
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            font.family: "Source Han Sans CN"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                sp.loadFromFile()
                textFolderPath.text=sp.getWorkPath()
                serverURL.text=sp.getWsClientUrl()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
