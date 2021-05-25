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
            id: emailEdit
            x: 2
            height: 50
            color: "#f5f5f5"
            radius: 10
            anchors.topMargin: 40
            anchors.left: parent.left
            anchors.top: element.bottom
            anchors.right: parent.right
            Image {
                id: image1
                y: 0
                width: 30
                height: 34
                source: "images/email.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 10
            }

            TextField {
                id: emailField
                x: 46
                width: 290
                height: 24
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                placeholderText: qsTr("邮箱")
                font.pixelSize: 20
                background: Rectangle {
                    color: "#f5f5f5"
                    border.width: 0
                    anchors.fill: parent
                }
                font.family: "Source Han Sans CN"
            }
            anchors.leftMargin: 32
            anchors.rightMargin: 32
        }

        Rectangle {
            id: passswordEdit
            x: -3
            y: 4
            height: 50
            color: "#f5f5f5"
            radius: 10
            anchors.topMargin: 12
            anchors.left: parent.left
            anchors.rightMargin: 32
            Image {
                id: image2
                y: 0
                width: 30
                height: 34
                anchors.left: parent.left
                source: "images/password.png"
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 10
            }

            TextField {
                id: passwordField
                x: 46
                width: 290
                height: 24
                text: ""
                font.family: "Source Han Sans CN"
                background: Rectangle {
                    color: "#f5f5f5"
                    border.width: 0
                    anchors.fill: parent
                }
                anchors.right: parent.right
                placeholderText: qsTr("密码")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 20
            }
            anchors.right: parent.right
            anchors.top: emailEdit.bottom
            anchors.leftMargin: 32
        }

        Rectangle {
            id: passswordConfirm
            x: -2
            y: 7
            height: 50
            color: "#f5f5f5"
            radius: 10
            anchors.topMargin: 74
            anchors.left: parent.left
            anchors.rightMargin: 32
            Image {
                id: image3
                y: 0
                width: 30
                height: 34
                anchors.left: parent.left
                source: "images/password.png"
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 10
            }

            TextField {
                id: passwordConfirm
                x: 46
                width: 290
                height: 24
                font.family: "Source Han Sans CN"
                background: Rectangle {
                    color: "#f5f5f5"
                    border.width: 0
                    anchors.fill: parent
                }
                anchors.right: parent.right
                placeholderText: qsTr("确认密码")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 20
            }
            anchors.right: parent.right
            anchors.top: emailEdit.bottom
            anchors.leftMargin: 32
        }
    }


