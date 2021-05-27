import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: newAClass
    width: 720
    height: 461
    radius: 20
    clip: true
    Text {
        id: element28
        width: 128
        height: 43
        text: qsTr("创建班级")
        anchors.top: parent.top
        verticalAlignment: Text.AlignVCenter
        font.weight: Font.Medium
        anchors.topMargin: 36
        font.family: "Source Han Sans CN"
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 32
    }

    Rectangle {
        id: name
        width: 280
        height: 37
        anchors.left: parent.left
        anchors.top: element28.bottom
        anchors.topMargin: 24
        anchors.leftMargin: 52

        Text {
            id: element29
            width: 48
            height: 32
            text: qsTr("名称")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 24
        }

        TextField {
            id: nameField
            width: 210
            height: 40
            verticalAlignment: "AlignVCenter"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            font.pixelSize: 22
            horizontalAlignment: Text.AlignRight
            selectByMouse: true
            font.family: "Source Han Sans CN"
            placeholderText: qsTr("输入班级名称")
            background: Rectangle {
                anchors.fill: parent
                border.width: 0
            }
        }
    }

    Rectangle {
        id: time
        width: 280
        height: 37
        anchors.right: parent.right
        anchors.top: element28.bottom
        anchors.topMargin: 24
        anchors.rightMargin: 52
        Text {
            id: element31
            width: 96
            height: 32
            text: qsTr("上课时间")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            font.family: "Source Han Sans CN"
            font.pointSize: 24
        }

        TextField {
            id: timeField
            width: 160
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            font.pixelSize: 22
            horizontalAlignment: Text.AlignRight
            verticalAlignment: "AlignVCenter"
            placeholderText: qsTr("输入上课时间")
            font.family: "Source Han Sans CN"
            selectByMouse: true
            background: Rectangle {
                border.width: 0
                anchors.fill: parent
            }
        }
    }

    Rectangle {
        id: location
        width: 280
        height: 37
        anchors.left: parent.left
        anchors.top: name.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 52
        Text {
            id: element33
            height: 32
            text: qsTr("上课地点")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            font.family: "Source Han Sans CN"
            font.pointSize: 24
        }

        TextField {
            id: locationField
            width: 160
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            font.pixelSize: 22
            horizontalAlignment: Text.AlignRight
            verticalAlignment: "AlignVCenter"
            placeholderText: qsTr("输入上课地点")
            font.family: "Source Han Sans CN"
            selectByMouse: true
            background: Rectangle {
                border.width: 0
                anchors.fill: parent
            }
        }
    }

    Rectangle {
        id: rectangle19
        width: 616
        height: 100
        color: "#f5f5f5"
        anchors.top: location.bottom
        anchors.topMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 10

        Text {
            id: element35
            height: 37
            text: qsTr("邀请码")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 28
        }

        TextField {
            id: codeField
            width: 280
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            font.pixelSize: 40
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: "AlignVCenter"
            anchors.rightMargin: 130
            placeholderText: qsTr("自选4位邀请码")
            font.family: "Source Han Sans CN"
            maximumLength: 4
            selectByMouse: true
            background: Rectangle {
                color: "#00000000"
                border.width: 0
                anchors.fill: parent
            }
        }
    }

    Rectangle {
        id: rectangle20
        width: 218
        height: 56
        radius: 10;
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 36
        color: "#0098f7"
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: submitBtn
            y: 11
            height: 32
            color: "#ffffff"
            text: qsTr("创建")
            font.weight: Font.Medium
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 24
        }

        MouseArea {
            id: mouseArea18
            anchors.fill: parent
            onClicked: {
                if (nameField.text == "" || codeField.text == "") {
                    return
                } else {
                    var code = classVC.addClass(nameField.text, locationField.text || "未填写", timeField.text || "未填写", codeField.text)
                    switch (code) {
                    case 0:
                        newClass.close()
                        classPage.refresh()
                        break
                    case 1:
                        submitBtn.text = "邀请码被占用"
                        break
                    case 2:
                        submitBtn.text = "存在同名班级"
                        break
                    case 3:
                        submitBtn.text = "操作失败"
                        break
                    default:
                        submitBtn.text = "操作失败"
                        break
                    }
                }
            }
        }
    }

    Image {
        id: image1
        width: 32
        height: 32
        anchors.right: parent.right
        anchors.top: parent.top
        source: "images/close.png"
        anchors.topMargin: 20
        anchors.rightMargin: 20
        fillMode: Image.PreserveAspectFit

        MouseArea {
            id: mouseArea17
            anchors.fill: parent
            onClicked: {
                newClass.close()
            }
        }
    }
}
