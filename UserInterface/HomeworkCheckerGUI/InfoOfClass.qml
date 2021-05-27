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

    property int classId
    property string className: "加载中"
    property string inviteCode: "加载中"
    property string time: "加载中"
    property string location: "加载中"
    property int count: 0

    function show(item) {
        classId = item.id
        className = item.name
        inviteCode = item.code
        time = item.time
        location = item.location
        count = item.count
        classInfoPopup.open()
    }

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
        font.pixelSize: 32
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
            font.pixelSize: 24
        }

        Text {
            id: element30
            height: 32
            text: className
            anchors.right: parent.right
            verticalAlignment: Text.AlignVCenter
            anchors.rightMargin: 0
            horizontalAlignment: Text.AlignRight
            font.family: "Source Han Sans CN"
            font.pixelSize: 24
            anchors.top: parent.top
        }
        anchors.left: parent.left
        anchors.topMargin: 24
        anchors.top: element28.bottom
    }

    Rectangle {
        id: countLabel
        width: 258
        height: 37
        anchors.right: parent.right
        Text {
            id: element31
            width: 96
            height: 32
            text: qsTr("学生人数")
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
            anchors.left: parent.left
            font.pixelSize: 24
        }

        Text {
            id: element32
            x: 129
            height: 32
            text: count
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight
            font.family: "Source Han Sans CN"
            font.pixelSize: 24
            anchors.top: parent.top
        }
        anchors.rightMargin: 52
        anchors.topMargin: 24
        anchors.top: element28.bottom
    }

    Rectangle {
        id: timeLabel
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
            font.pixelSize: 24
        }

        Text {
            id: element34
            x: 129
            height: 32
            text: time
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight
            font.family: "Source Han Sans CN"
            font.pixelSize: 24
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
            text: qsTr("邀请码")
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 20
            horizontalAlignment: Text.AlignLeft
            font.family: "Source Han Sans CN"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 28
        }

        Text {
            id: inviteCodeLabel
            x: 311
            height: 53
            text: inviteCode
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            font.pixelSize: 40
        }
        anchors.topMargin: 32
        anchors.top: timeLabel.bottom
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
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea18
            anchors.fill: parent
            onClicked: {
                if (element37.text == "结课") {
                    element37.text = "确认结课"
                } else {
                    if (classVC.endClass(classId) === 0) {
                        element37.text = "操作成功"
                        classInfoPopup.close()
                        classPage.refresh()
                    } else {
                        element37.text = "操作失败"
                    }
                }
            }
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
                element37.text = "结课"
                classInfoPopup.close()
            }
        }
    }

    Rectangle {
        id: locationLabel
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
            font.pixelSize: 24
        }

        Text {
            id: element39
            x: 129
            height: 32
            text: location
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight
            font.family: "Source Han Sans CN"
            font.pixelSize: 24
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
