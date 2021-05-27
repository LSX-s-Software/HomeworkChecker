import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: infoOfClass
    width: 720
    height: 461
    color: "#ffffff"
    radius: 20
    clip: true
    Text {
        id: element28
        width: 128
        height: 43
        text: qsTr("班级信息")
        verticalAlignment: Text.AlignVCenter
        font.weight: Font.Medium
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: "Source Han Sans CN"
        anchors.topMargin: 36
        font.pointSize: 32
        anchors.top: parent.top
    }

    Rectangle {
        id: name
        width: 258
        height: 37
        anchors.leftMargin: 52
        Text {
            id: element29
            width: 48
            height: 32
            text: qsTr("名称")
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            anchors.left: parent.left
            font.pointSize: 24
        }

        Text {
            id: element30
            x: 129
            height: 32
            text: qsTr("2020级计卓")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            font.pointSize: 24
            anchors.top: parent.top
        }
        anchors.left: parent.left
        anchors.topMargin: 24
        anchors.top: element28.bottom
    }

    Rectangle {
        id: time
        width: 258
        height: 37
        anchors.right: parent.right
        Text {
            id: element31
            width: 96
            height: 32
            text: qsTr("邀请码")
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            anchors.left: parent.left
            font.pointSize: 24
        }

        Text {
            id: element32
            x: 129
            height: 32
            text: qsTr("3CE4")
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            font.pointSize: 24
            anchors.top: parent.top
        }
        anchors.rightMargin: 52
        anchors.topMargin: 24
        anchors.top: element28.bottom
    }

    Rectangle {
        id: location
        width: 258
        height: 37
        anchors.leftMargin: 52
        Text {
            id: element33
            height: 32
            text: qsTr("上课时间")
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            anchors.left: parent.left
            font.pointSize: 24
        }

        Text {
            id: element34
            x: 129
            height: 32
            text: qsTr("周五上午")
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            font.pointSize: 24
            anchors.top: parent.top
        }
        anchors.left: parent.left
        anchors.topMargin: 20
        anchors.top: name.bottom
    }

    Rectangle {
        id: rectangle19
        width: 616
        height: 100
        color: "#f5f5f5"
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: element35
            height: 37
            text: qsTr("学生")
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 20
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 28
        }

        Image {
            id: studentAvatar
            x: 100
            y: 17
            width: 516
            height: 66
            source: "images/student.png"
            fillMode: Image.PreserveAspectFit
        }
        anchors.topMargin: 32
        anchors.top: location.bottom
    }

    Rectangle {
        id: finish
        x: 286
        width: 148
        height: 56
        color: "#fa5151"
        radius: 10
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: element37
            y: 11
            height: 32
            color: "#ffffff"
            text: qsTr("结课")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            font.pointSize: 24
        }

        MouseArea {
            id: mouseArea18
            anchors.fill: parent
        }
        anchors.bottomMargin: 36
    }

    Image {
        id: close
        width: 32
        height: 32
        anchors.right: parent.right
        anchors.top: parent.top
        source: "images/close.png"
        anchors.topMargin: 20
        anchors.rightMargin: 20
        MouseArea {
            id: mouseArea17
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                info.close()
            }
        }
    }

    Rectangle {
        id: invitition
        x: 410
        y: 165
        width: 258
        height: 37
        anchors.right: parent.right
        Text {
            id: element38
            width: 96
            height: 32
            text: qsTr("上课地点")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            anchors.left: parent.left
            font.pointSize: 24
        }

        Text {
            id: element39
            x: 129
            height: 32
            text: qsTr("3区1-507")
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            font.pointSize: 24
            anchors.top: parent.top
        }
        anchors.rightMargin: 52
        anchors.topMargin: 81
        anchors.top: element28.bottom
    }

    Rectangle {
        id: editInFo
        x: 52
        y: 369
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10

        Text {
            id: element
            color: "#0098f7"
            text: qsTr("编辑信息")
            font.weight: Font.Medium
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

    Rectangle {
        id: checkMark
        x: 450
        y: 369
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10

        Text {
            id: element1
            color: "#0098f7"
            text: qsTr("查看成绩")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
        }
    }
}
