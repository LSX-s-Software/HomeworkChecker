import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import Account 1.0

Rectangle {
    id: loginPage
    width: 400
    height: 378
    color: "#ffffff"
    radius: 20
    clip: true

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

    Text {
        id: title
        width: 80
        height: 40
        text: qsTr("登录")
        verticalAlignment: Text.AlignVCenter
        font.family: "Source Han Sans CN"
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40
    }

    Rectangle {
        id: emailEdit
        height: 50
        color: "#f5f5f5"
        radius: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: title.bottom
        anchors.topMargin: 40
        anchors.rightMargin: 32
        anchors.leftMargin: 32

        Image {
            id: image
            y: 0
            width: 30
            height: 34
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            fillMode: Image.PreserveAspectFit
            source: "images/email.png"
        }

        TextField {
            id: emailField
            x: 46
            width: 290
            height: 40
            verticalAlignment: "AlignVCenter"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            font.pixelSize: 20
            selectByMouse: true
            font.family: "Source Han Sans CN"
            placeholderText: qsTr("邮箱")
            background: Rectangle {
                anchors.fill: parent
                border.width: 0
                color: "#f5f5f5"
            }
        }
    }

    Rectangle {
        id: passwordEdit
        height: 50
        color: "#f5f5f5"
        radius: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: emailEdit.bottom
        anchors.topMargin: 12
        anchors.rightMargin: 32
        anchors.leftMargin: 32
        Image {
            id: image1
            y: 0
            width: 30
            height: 34
            anchors.leftMargin: 10
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: parent.verticalCenter
            source: "images/password.png"
            anchors.left: parent.left
        }
        TextField {
            id: passwordField
            x: 46
            width: 290
            height: 40
            verticalAlignment: "AlignVCenter"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            font.pixelSize: 20
            passwordCharacter: "●"
            echoMode: TextField.Password
            selectByMouse: true
            font.family: "Source Han Sans CN"
            placeholderText: qsTr("密码")
            background: Rectangle {
                anchors.fill: parent
                border.width: 0
                color: "#f5f5f5"
            }
        }
    }

    Rectangle {
        id: signAccountBtn
        width: 144
        height: 18
        color: "#ffffff"
        anchors.top: passwordEdit.bottom
        anchors.topMargin: 12
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: element1
            color: "#0098f7"
            text: qsTr("还没有账号？注册")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 18
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                logInPopup.close()
                regPopup.open()
            }
        }
    }

    Rectangle {
        id: logInBtn
        x: 100
        y: 300
        width: 336
        height: 60
        color: "#0098f7"
        radius: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: logInBtnText
            color: "#ffffff"
            text: qsTr("登录")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: {
                let result = account.login(emailField.text, passwordField.text);
                switch (result) {
                case 0:
                    logInBtnText.text = "登录成功"
                    generalPage.visible = true
                    generalPage.refresh()
                    launchScreen.visible = false
                    logInPopup.close()
                    break
                case 1:
                    logInBtnText.text = "用户不存在"
                    break
                case 2:
                    logInBtnText.text = "密码错误"
                    break
                default:
                    logInBtnText.text = "登录失败"
                }
                setTimeout(() => { logInBtnText.text = "登录" }, 1500)
            }
        }
    }

}
