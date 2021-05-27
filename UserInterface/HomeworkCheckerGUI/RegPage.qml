import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Account 1.0

Rectangle {
    id: regPage
    width: 400
    height: 500
    color: "#ffffff"
    radius: 20
    clip: true
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

    Account {
        id: account
    }

    Timer {id: timer}
    function setTimeout(cb,delayTime) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();
    }

    Rectangle {
        id: logInBtn
        y: 300
        width: 144
        height: 18
        color: "#ffffff"
        anchors.bottom: nextBtn.top
        anchors.bottomMargin: 24
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
            onClicked: {
                regPopup.close()
                logInPopup.open()
            }
        }
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: nextBtn
        x: 100
        width: 336
        height: 60
        radius: 10
        clip: true
        color: "#0098f7"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32
        Text {
            id: nextBtnTxt
            color: "#ffffff"
            text: qsTr("注册")
            font.bold: false
            font.weight: Font.Medium
            anchors.fill: parent
            font.pixelSize: 28
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: {
                if (emailField.text == "" || passwordField.text == "" || passwordConfirm.text == "" || nameField.text == "") {
                    nextBtnTxt.text = "请填写完全部内容再提交"
                } else {
                    if (passwordField.text == passwordConfirm.text) {
                        var result = account.reg(emailField.text, passwordField.text)
                        if (result === 0) {
                            account.userName = nameField.text
                            nextBtnTxt.text = "注册成功"
                            generalPage.visible = true
                            generalPage.refresh()
                            setTimeout(function () {
                                regPopup.close()
                            }, 1500)
                        } else {
                            nextBtnTxt.text = "注册失败"
                        }
                    } else {
                        nextBtnTxt.text = "两次输入的密码不一致"
                    }
                }
                setTimeout(function () {
                    nextBtnTxt.text = "注册"
                }, 1500)
            }
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
            height: 40
            verticalAlignment: "AlignVCenter"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            placeholderText: qsTr("邮箱")
            selectByMouse: true
            font.pixelSize: 20
            background: Rectangle {
                color: "#f5f5f5"
                border.width: 0
                anchors.fill: parent
            }
            font.family: "Source Han Sans CN"
            maximumLength: 50
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
            height: 40
            text: ""
            font.family: "Source Han Sans CN"
            background: Rectangle {
                color: "#f5f5f5"
                border.width: 0
                anchors.fill: parent
            }
            anchors.right: parent.right
            placeholderText: qsTr("密码")
            passwordCharacter: "·"
            echoMode: TextField.Password
            selectByMouse: true
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 20
            maximumLength: 25
        }
        anchors.right: parent.right
        anchors.top: emailEdit.bottom
        anchors.leftMargin: 32
    }

    Rectangle {
        id: passswordConfirm
        height: 50
        color: "#f5f5f5"
        radius: 10
        anchors.topMargin: 12
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
            height: 40
            font.family: "Source Han Sans CN"
            background: Rectangle {
                color: "#f5f5f5"
                border.width: 0
                anchors.fill: parent
            }
            anchors.right: parent.right
            placeholderText: qsTr("确认密码")
            passwordCharacter: "·"
            echoMode: TextField.Password
            selectByMouse: true
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 20
            maximumLength: 25
        }
        anchors.right: parent.right
        anchors.top: passswordEdit.bottom
        anchors.leftMargin: 32
    }

    Rectangle {
        id: nameEdit
        height: 50
        color: "#f5f5f5"
        radius: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: passswordConfirm.bottom
        Image {
            id: image4
            y: 0
            width: 30
            height: 34
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            source: "images/name.png"
            fillMode: Image.PreserveAspectFit
            anchors.leftMargin: 10
        }

        TextField {
            id: nameField
            x: 46
            width: 290
            height: 40
            verticalAlignment: "AlignVCenter"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            font.pixelSize: 20
            placeholderText: qsTr("姓名")
            font.family: "Source Han Sans CN"
            background: Rectangle {
                color: "#f5f5f5"
                border.width: 0
                anchors.fill: parent
            }
            selectByMouse: true
            maximumLength: 15
        }
        anchors.topMargin: 12
        anchors.rightMargin: 32
        anchors.leftMargin: 32
    }
}


