import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12


Rectangle {
    id: rectangle
    x: 0
    y: 0
    width: 1046
    height: 768
    color: "#ffffff"
    radius: 10
    border.width: 1
    border.color: "#00000000"

    Rectangle {
        id: rectangle1
        y: 203
        width: 748
        height: 540
        color: "#ffffff"
        radius: 1
        border.width: 1
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: element
            text: qsTr("homework")
            anchors.fill: parent
            font.pixelSize: 20
        }
    }

    Text {
        id: element1
        width: 160
        height: 40
        text: qsTr("批改作业")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40
    }

    Rectangle {
        id: rectangle2
        width: 76
        height: 28
        color: "#ffffff"
        anchors.top: parent.top
        anchors.topMargin: 46
        anchors.left: parent.left
        anchors.leftMargin: 28

        Text {
            id: element2
            color: "#0098f7"
            text: qsTr("返回")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea
            width: 100
            height: 100
        }
    }

    Text {
        id: element3
        x: 808
        y: 114
        width: 56
        height: 28
        text: qsTr("附件")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 28
    }

    Rectangle {
        id: rectangle3
        x: 808
        y: 163
        width: 198
        height: 70
        color: "#f5f5f5"

        Text {
            id: element4
            text: qsTr("6-28.cpp")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
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
    D{i:1;anchors_x:134}D{i:4;anchors_x:76;anchors_y:46}D{i:10;anchors_height:100;anchors_width:100}
}
 ##^##*/
