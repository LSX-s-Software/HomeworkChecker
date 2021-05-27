import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: rectangle
    width: 1046
    height: 768
    color: "#ffffff"
    //Component
    Component{
        id: studentListItem
        Rectangle {
            width: listView.width
            height: 62
            color: "#f5f5f5"

            Text {
                id: nameAndNumber
                text: name+"("+number+")"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 16
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 28
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked:
                    markPage.push(scoreOfEach)
            }

            Text {
                id: scoreOfStudent
                width: 45
                text: score
                anchors.right: parent.right
                anchors.rightMargin: 45
                horizontalAlignment: Text.AlignLeft
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 28
                color: "#707070"
            }

            Image {
                width: 9
                height: 28
                anchors.rightMargin: 20
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "images/more.png"
            }
        }
    }

    //endcompoennt

    Rectangle {
        id: backBtn
        x: -4
        y: 3
        width: 76
        height: 28
        color: "#ffffff"
        anchors.leftMargin: 28
        anchors.topMargin: 46
        anchors.left: parent.left
        Text {
            id: element3
            color: "#0098f7"
            text: qsTr("返回")
            font.weight: Font.Medium
            font.pixelSize: 28
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            anchors.fill: parent
            horizontalAlignment: Text.AlignRight
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: markPage.pop()
        }

        Image {
            id: image1
            width: 25
            height: 22
            source: "images/backBtn.png"
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: parent.verticalCenter
        }
        anchors.top: parent.top
    }

    Text {
        id: title
        height: 40
        text: qsTr("2019级计卓")
        verticalAlignment: Text.AlignVCenter
        font.family: "Source Han Sans CN"
        font.weight: Font.Medium
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40
    }

    Rectangle {
        id: rectangle1
        x: 904
        y: 39
        width: 110
        height: 42
        color: "#0098f7"
        radius: 10

        Text {
            id: element
            color: "#ffffff"
            text: qsTr("导出成绩")
            font.weight: Font.Medium
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 20
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }

    Rectangle {
        id: averageScore
        width: 60
        height: 72
        color: "#ffffff"
        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.leftMargin: 100
        anchors.topMargin: 24

        Text {
            id: average
            height: 40
            text: qsTr("89")
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            font.pixelSize: 40
        }

        Text {
            id: element2
            width: 60
            height: 20
            text: qsTr("平均分")
            anchors.bottom: parent.bottom
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
    }

    Rectangle {
        id: highestScore
        width: 60
        height: 72
        color: "#ffffff"
        anchors.top: title.bottom
        anchors.topMargin: 24
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: highest
            height: 40
            text: qsTr("89")
            anchors.topMargin: 0
            font.pixelSize: 40
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            anchors.top: parent.top
        }

        Text {
            id: element4
            width: 60
            height: 20
            text: qsTr("最高分")
            font.pixelSize: 20
            anchors.bottom: parent.bottom
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
        }
    }

    ListView {
        id: listView
        width: 982
        height: 562
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        delegate: studentListItem
        clip: true
        model: ListModel {
            ListElement {
                name: "李四"
                number:"2020302111000"
                score:"89"
            }

            ListElement {
                name: "李四"
                number:"2020302111000"
                score:"89"
            }

            ListElement {
                name: "李四"
                number:"2020302111000"
                score:"89"
            }

            ListElement {
                name: "李四"
                number:"2020302111000"
                score:"89"
            }

            ListElement {
                name: "李四"
                number:"2020302111000"
                score:"89"
            }

            ListElement {
                name: "李四"
                number:"2020302111000"
                score:"89"
            }

            ListElement {
                name: "李四"
                number:"2020302111000"
                score:"89"
            }
        }

    }

    Rectangle {
        id: lowestScore
        x: 889
        width: 60
        height: 72
        color: "#ffffff"
        anchors.right: parent.right
        anchors.top: title.bottom
        anchors.rightMargin: 100
        anchors.topMargin: 24
        Text {
            id: lowest
            height: 40
            text: qsTr("89")
            anchors.topMargin: 0
            font.pixelSize: 40
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            anchors.top: parent.top
        }

        Text {
            id: element5
            width: 60
            height: 20
            text: qsTr("最低分")
            font.pixelSize: 20
            anchors.bottom: parent.bottom
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Component{
        id:scoreOfEach
        ScoreWithStudent{}
    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:15}D{i:18}D{i:30}
}
##^##*/
