import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: logInPage
    width: 400
    height: 378
    color: "#ffffff"

    Text {
        id: title
        width: 80
        height: 40
        text: qsTr("登录")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40
    }

    Rectangle {
        id: emailEdit
        x: 21
        y: 120
        width: 336
        height: 50
        color: "#f5f5f5"
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: image
            y: 0
            width: 30
            height: 34
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            fillMode: Image.PreserveAspectFit
            source: "images/at.png"
        }

        TextInput {
            id: textInput1
            x: 46
            width: 290
            height: 20
            text: qsTr("邮箱")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            font.pixelSize: 20
        }
    }

    Rectangle {
        id: passwordEdit
        x: 16
        y: 182
        width: 336
        height: 50
        color: "#f5f5f5"
        radius: 10
        anchors.horizontalCenterOffset: 0
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
            text: qsTr("密码")
            anchors.right: parent.right
            font.pixelSize: 20
            anchors.verticalCenter: parent.verticalCenter
        }
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: signAccountBtn
        y: 244
        width: 144
        height: 18
        color: "#ffffff"
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: element1
            color: "#0098f7"
            text: qsTr("还没有账号？注册")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 18
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }

    Rectangle {
        id: logInBtn
        x: 100
        y: 300
        width: 336
        height: 60
        color: "#0098f7"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: element2
            color: "#ffffff"
            text: qsTr("登录")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
        }
    }

}





/*##^## Designer {
    D{i:13;anchors_height:100;anchors_width:100}
}
 ##^##*/
