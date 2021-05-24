import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12


Rectangle {
    id: arrangement
    width: 922
    height: 640
    color: "#ffffff"

    Text {
        id: element
        width: 128
        height: 32
        text: qsTr("布置作业")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 27
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 32
    }

    Rectangle {
        id: title
        x: 53
        y: 98
        width: 400
        height: 33
        anchors.leftMargin: 52
        anchors.top: element28.bottom
        Text {
            id: element29
            width: 48
            height: 32
            text: qsTr("标题")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 0
            font.pointSize: 24
            font.weight: Font.Medium
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
        }

        Text {
            id: element30
            x: 129
            height: 32
            text: qsTr("第七章作业")
            anchors.right: parent.right
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 24
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
        }
        anchors.left: parent.left
        anchors.topMargin: 24
    }

    Rectangle {
        id: targetClass
        x: 470
        y: 98
        width: 400
        height: 33
        anchors.top: element28.bottom
        Text {
            id: element31
            width: 48
            height: 32
            text: qsTr("目标班级")
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 24
            font.weight: Font.Bold
            horizontalAlignment: Text.AlignLeft
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
            font.bold: true
        }

        Text {
            id: element32
            x: 129
            height: 32
            text: qsTr("第七章作业")
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 24
            anchors.right: parent.right
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Han Sans CN"
        }
        anchors.topMargin: 24
    }

    Rectangle {
        id: deadline
        x: 53
        y: 151
        width: 817
        height: 33
        anchors.top: element28.bottom
        Text {
            id: element33
            width: 48
            height: 32
            text: qsTr("截止时间")
            font.italic: false
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 24
            font.weight: Font.Medium
            horizontalAlignment: Text.AlignLeft
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
            font.bold: true
        }
        
        TextInput {
            id: textInput
            width: 252
            height: 32
            text: qsTr("2021年6月1日 23:59:59")
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }
        anchors.topMargin: 24
    }

    Rectangle {
        id: describtion
        x: 52
        y: 204
        width: 818
        height: 338
        color: "#ffffff"

        Text {
            id: element1
            x: 0
            width: 96
            height: 24
            text: qsTr("作业描述")
            anchors.top: parent.top
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }

        Rectangle {
            id: rectangle2
            x: 116
            width: 702
            height: 329
            color: "#ffffff"

            TextArea {
                id: textArea
                text: qsTr("Text Area")
                anchors.fill: parent
            }
        }
    }

    Rectangle {
        id: setBtn
        width: 218
        height: 56
        color: "#0098f7"
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32

        Text {
            id: element2
            color: "#ffffff"
            text: qsTr("创建")
            font.bold: true
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
}





/*##^## Designer {
    D{i:12;anchors_y:30}D{i:14;anchors_height:329;anchors_width:702;anchors_x:39;anchors_y:0}
D{i:17;anchors_height:100;anchors_width:100}
}
 ##^##*/
