import QtQuick 2.0

Rectangle {
    id: correctHomework
    x: 0
    y: 0
    width: 1046
    height: 768
    color: "#ffffff"
    radius: 10
    Rectangle {
        id: homeworkOfStudents
        y: 203
        width: 748
        height: 540
        color: "#ffffff"
        radius: 1
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter
        Text {
            id: element
            text: qsTr("homework")
            anchors.fill: parent
            font.pixelSize: 20
        }
        anchors.left: parent.left
        border.width: 1
    }

    Text {
        id: element1
        width: 160
        height: 40
        text: qsTr("批改作业")
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        anchors.topMargin: 40
        font.pixelSize: 40
    }

    Rectangle {
        id: backBtn
        width: 76
        height: 28
        color: "#ffffff"
        anchors.leftMargin: 28
        anchors.top: parent.top
        Text {
            id: element2
            color: "#0098f7"
            text: qsTr("返回")
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked:
                taskPage.pop()
        }

        Image {
            id: image
            width: 25
            height: 22
            source: "images/backBtn.png"
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: parent.verticalCenter
        }
        anchors.left: parent.left
        anchors.topMargin: 46
    }

    Text {
        id: element3
        x: 808
        y: 114
        width: 56
        height: 28
        text: qsTr("附件")
        verticalAlignment: Text.AlignVCenter
        font.weight: Font.Bold
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 28
    }

    Rectangle {
        id: addition
        x: 808
        y: 163
        width: 198
        height: 70
        color: "#f5f5f5"
        radius: 10
        Text {
            id: element4
            text: qsTr("6-28.cpp")
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
        }
    }

    Rectangle {
        id: markBtn
        x: 788
        y: 676
        width: 218
        height: 56
        color: "#0098f7"
        radius: 10
        Text {
            id: element7
            color: "#ffffff"
            text: qsTr("打分")
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            font.weight: Font.Bold
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea4
            anchors.fill: parent
        }
    }

    Rectangle {
        id: comment
        x: 40
        y: 680
        width: 541
        height: 48
        color: "#f5f5f5"

        TextInput {
            id: textInput
            text: qsTr("评语")

            horizontalAlignment: Text.AlignLeft
            anchors.fill: parent
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea2
            anchors.fill: parent
        }
    }

    Rectangle {
        id: score
        x: 597
        y: 680
        width: 175
        height: 48
        color: "#f5f5f5"

        TextInput {
            id: textInput1
            text: qsTr("100")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea3
            anchors.fill: parent
        }
    }
    border.color: "#00000000"
    border.width: 1
}










/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:16}D{i:17}D{i:15}D{i:19}D{i:20}
}
##^##*/
