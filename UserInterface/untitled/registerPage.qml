import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

    Rectangle {
        id: logInPage
        width: 400
        height: 440
        color: "#ffffff"
        Text {
            id: element
            width: 80
            height: 40
            text: qsTr("注册")
            anchors.topMargin: 40
            anchors.top: parent.top
            font.pixelSize: 40
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: passwordEdit
            x: 21
            y: 182
            width: 336
            height: 50
            color: "#f5f5f5"
            radius: 10
            anchors.horizontalCenterOffset: 12
            Image {
                id: image
                y: 0
                width: 30
                height: 34
                anchors.leftMargin: 10
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                source: "images/email-1.png"
                anchors.left: parent.left
            }

            TextInput {
                id: textInput1
                x: 46
                width: 290
                height: 20
                text: qsTr("密码")
                anchors.right: parent.right
                font.pixelSize: 20
                anchors.verticalCenter: parent.verticalCenter
            }
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: passwordConfirm
            x: 16
            y: 244
            width: 336
            height: 50
            color: "#f5f5f5"
            radius: 10
            Image {
                id: image1
                y: 0
                width: 30
                height: 34
                anchors.leftMargin: 10
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                source: "images/email-1.png"
                anchors.left: parent.left
            }

            TextInput {
                id: textInput2
                x: 46
                width: 290
                height: 20
                text: qsTr("确认密码")
                anchors.right: parent.right
                font.pixelSize: 20
                anchors.verticalCenter: parent.verticalCenter
            }
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 12
        }

        Rectangle {
            id: logInBtn
            y: 300
            width: 144
            height: 18
            color: "#ffffff"
            anchors.horizontalCenterOffset: 0
            Text {
                id: element1
                color: "#0098f7"
                text: qsTr("已有账号？登录")
                anchors.fill: parent
                font.pixelSize: 18
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
            }
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: nextBtn
            x: 100
            y: 300
            width: 336
            height: 60
            color: "#0098f7"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 32
            Text {
                id: element2
                color: "#ffffff"
                text: qsTr("下一步")
                anchors.fill: parent
                font.pixelSize: 28
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                id: mouseArea1
                anchors.fill: parent
            }
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: emailEdit1
            x: 26
            y: 120
            width: 336
            height: 50
            color: "#f5f5f5"
            radius: 10
            anchors.horizontalCenterOffset: 12
            Image {
                id: image2
                y: 0
                width: 30
                height: 34
                anchors.leftMargin: 10
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                source: "images/at.png"
                anchors.left: parent.left
            }

            TextInput {
                id: textInput3
                x: 46
                width: 290
                height: 20
                text: qsTr("用于收发作业的邮箱")
                anchors.right: parent.right
                font.pixelSize: 20
                anchors.verticalCenter: parent.verticalCenter
            }
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }


