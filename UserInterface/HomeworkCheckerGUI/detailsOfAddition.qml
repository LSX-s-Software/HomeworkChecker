
import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: detailsOfAddition
    width: 1046
    height: 768
    color: "#ffffff"

    Text {
        id: title
        x: 496
        width: 160
        height: 40
        text: qsTr("批改作业")
        font.weight: Font.Medium
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40
    }

    Rectangle {
        id: component
        width: 966
        height: 500
        color: "#ffffff"
        border.width: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 120
        anchors.horizontalCenter: parent.horizontalCenter

        MouseArea {
            id: mouseArea3
            anchors.fill: parent
        }

        TextArea {
            id: textArea
            text: qsTr("Text Area")
            anchors.fill: parent
        }
    }

    Text {
        id: element1
        x: 40
        y: 112
        width: 112
        height: 28
        text: qsTr("附件内容")
        font.weight: Font.Medium
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 28
    }

    Rectangle {
        id: backBtn
        x: 40
        y: 676
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10

        Text {
            id: element2
            color: "#0098f7"
            text: qsTr("返回")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea2
            anchors.fill: parent
            onClicked:
                taskPage.pop()
        }
    }

    Rectangle {
        id: runBtn
        x: 414
        y: 682
        width: 218
        height: 56
        color: "#0098f7"
        radius: 10
        Text {
            id: element3
            color: "#ffffff"
            text: qsTr("编译并运行")
            font.weight: Font.Medium
            font.bold: false
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
        }
    }

    Rectangle {
        id: scoreBtn
        x: 788
        y: 678
        width: 218
        height: 56
        color: "#0098f7"
        radius: 10
        Text {
            id: element4
            color: "#ffffff"
            text: qsTr("打分")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
            font.bold: false
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked:
                taskPage.push(mark)
        }
    }

    Component{
        id:mark
        MarkHomework{}
    }
}















/*##^## Designer {
    D{i:1;anchors_y:60}D{i:3;anchors_height:100;anchors_width:100}D{i:7;anchors_height:100;anchors_width:100}
D{i:10;anchors_height:100;anchors_width:100}D{i:13;anchors_height:100;anchors_width:100}
D{i:14;anchors_x:"-374";anchors_y:4}
}
 ##^##*/
