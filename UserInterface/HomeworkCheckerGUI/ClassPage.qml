import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: classPage
    width: 1046
    height: 768
    color: "#ffffff"

    Popup {
        id: newClass
        modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        width: 720
        height: 461
        focus: true
        clip: true
        anchors.centerIn: classPage
        background: Rectangle {
            radius: 20
        }
        contentItem: NewAClass {
            id: newAClass
            anchors.fill: parent
        }
    }

    Popup {
        id: info
        modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        focus: true
        width: 720
        height: 461
        clip: true
        anchors.centerIn: classPage
        background: Rectangle {
            radius: 20
        }
        contentItem: InfoOfClass {
            id: infoOfClass
            anchors.fill: parent
        }
    }

    Text {
        id: title
        width: 240
        height: 53
        text: qsTr("已创建的班级")
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.topMargin: 32
        font.family: "Source Han Sans CN"
        font.pointSize: 40
        font.weight: Font.Medium
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: rectangle7
        width: 64
        height: 43
        color: "#ffffff"
        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.topMargin: 28
        anchors.leftMargin: 32
        Text {
            id: element4
            color: "#0098f7"
            text: qsTr("当前")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            font.pointSize: 32
            font.weight: Font.Medium
        }

        MouseArea {
            id: mouseArea4
            anchors.fill: parent
        }
    }

    Rectangle {
        id: rectangle8
        width: 64
        height: 43
        color: "#ffffff"
        anchors.left: rectangle7.right
        anchors.top: title.bottom
        anchors.topMargin: 28
        anchors.leftMargin: 32
        Text {
            id: element5
            color: "#707070"
            text: qsTr("过去")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            font.pointSize: 32
            font.weight: Font.Medium
        }

        MouseArea {
            id: mouseArea5
            anchors.fill: parent
        }
    }

    Component {
        id: classListItem
        Rectangle {
            id: rectangle
            width: listView.width
            height: 80
            color: "#f5f5f5"
            radius: 10

            Text {
                id: element12
                x: 16
                y: 9
                height: 37
                text: name
                verticalAlignment: Text.AlignVCenter
                font.family: "Source Han Sans CN"
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 28
            }

            Text {
                id: element13
                x: 16
                y: 44
                height: 27
                color: "#8f8f8f"
                text: time + "·" + location + "·" + count +"人"
                verticalAlignment: Text.AlignVCenter
                font.family: "Source Han Sans CN"
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 20
            }

            MouseArea {
                id: mouseArea6
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    info.open()
                }
            }
        }
    }

    ListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: rectangle7.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 24
        spacing: 12
        anchors.bottomMargin: 0
        anchors.leftMargin: 32
        anchors.rightMargin: 32
        clip: true
        delegate: classListItem
        model: ListModel {
            ListElement {
                name: "2020级计卓"
                time: "周五下午"
                location: "3区1-507"
                count: 30
            }
            ListElement {
                name: "2020级计卓"
                time: "周五下午"
                location: "3区1-507"
                count: 30
            }
            ListElement {
                name: "2020级计卓"
                time: "周五下午"
                location: "3区1-507"
                count: 30
            }
        }
    }

    Image {
        id: addBtn
        width: 60
        height: 60
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: "images/add@2x.png"
        anchors.bottomMargin: 28
        anchors.rightMargin: 32
        MouseArea {
            hoverEnabled: true
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                newClass.open()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
