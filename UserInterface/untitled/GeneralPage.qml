import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    id: generalPage
    width: 1046
    height: 768
    clip: false
    Rectangle {
        id: avatarMask
        width: 200
        height: 200
        radius: 100
        color: "#f5f5f5"
        border.width: 0
        anchors.top: parent.top
        anchors.topMargin: 120
        anchors.horizontalCenter: parent.horizontalCenter
        clip: true
        Image {
            id: avatar
            anchors.fill: parent
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: "images/person.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    Rectangle {
        id: rectangle1
        width: 300
        height: 185
        color: "#F5F5F5"
        radius: 10
        anchors.bottom: parent.bottom
        anchors.horizontalCenterOffset: -200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 50

        Image {
            id: image
            width: 60
            height: 60
            anchors.left: parent.left
            anchors.top: parent.top
            source: "images/homework@2x.png"
            anchors.leftMargin: 20
            anchors.topMargin: 20
            fillMode: Image.PreserveAspectFit
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }

        Text {
            id: element7
            width: 64
            height: 43
            text: qsTr("作业")
            anchors.verticalCenter: image.verticalCenter
            anchors.left: image.right
            anchors.top: parent.top
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 12
            anchors.topMargin: 24
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 32
        }

        Text {
            id: element8
            width: 108
            height: 27
            color: "#8f8f8f"
            text: qsTr("已批改/总数")
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 20
            anchors.bottomMargin: 20
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 20
        }

        Text {
            id: element9
            width: 108
            height: 27
            color: "#8f8f8f"
            text: qsTr("已提交/总数")
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.rightMargin: 20
            anchors.bottomMargin: 20
            font.family: "Source Han Sans CN"
            font.pointSize: 20
        }

    }

    Rectangle {
        id: rectangle2
        width: 300
        height: 185
        color: "#F5F5F5"
        radius: 10
        anchors.bottom: parent.bottom
        anchors.horizontalCenterOffset: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 50

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
        }

        Text {
            id: element10
            width: 128
            height: 43
            text: qsTr("批改进度")
            anchors.verticalCenter: image1.verticalCenter
            anchors.left: image1.right
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 32
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            anchors.leftMargin: 12
            anchors.topMargin: 24
            font.family: "Source Han Sans CN"
        }

        Text {
            id: element11
            width: 108
            height: 27
            color: "#8f8f8f"
            text: qsTr("已批改/总数")
            anchors.bottom: parent.bottom
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 20
            verticalAlignment: Text.AlignVCenter
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Source Han Sans CN"
        }

        Image {
            id: image1
            width: 60
            height: 60
            anchors.left: parent.left
            anchors.top: parent.top
            source: "images/progress@2x.png"
            fillMode: Image.PreserveAspectFit
            anchors.topMargin: 20
            anchors.leftMargin: 20
        }
    }

    Text {
        id: element6
        height: 48
        text: "早上好！张三老师"
        anchors.top: avatarMask.bottom
        verticalAlignment: Text.AlignVCenter
        anchors.topMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter
        font.weight: Font.Medium
        font.family: "Source Han Sans CN"
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 36
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
