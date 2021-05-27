import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    id: newAClass
    width: 720
    height: 461
    color: "#ffffff"
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
        width: 258
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
            anchors.left: parent.left
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 24
        }

        Text {
            id: element30
            x: 129
            height: 32
            text: qsTr("2020级计卓")
            anchors.top: parent.top
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 24
        }
    }

    Rectangle {
        id: time
        width: 258
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
            anchors.left: parent.left
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            font.family: "Source Han Sans CN"
            font.pointSize: 24
        }

        Text {
            id: element32
            x: 129
            height: 32
            text: qsTr("周五下午")
            anchors.right: parent.right
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            font.pointSize: 24
        }
    }

    Rectangle {
        id: location
        width: 258
        height: 37
        anchors.left: parent.left
        anchors.top: name.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 52
        Text {
            id: element33
            height: 32
            text: qsTr("上课地点")
            anchors.left: parent.left
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            font.family: "Source Han Sans CN"
            font.pointSize: 24
        }

        Text {
            id: element34
            x: 129
            height: 32
            text: qsTr("3区1-507")
            anchors.right: parent.right
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            font.pointSize: 24
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

        Text {
            id: element36
            x: 311
            height: 53
            text: qsTr("CDE2")
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 40
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
            id: element37
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
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 36
            anchors.horizontalCenter: parent.horizontalCenter
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
