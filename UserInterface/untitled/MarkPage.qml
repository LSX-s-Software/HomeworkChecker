import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
StackView {
    width: 1046
    height: 768
    clip: true
    id: markPage
    initialItem:Rectangle {

     y: -1
    width: markPage.width
    height: markPage.height
    color: "#ffffff"
    Text {
        id: element16
        x: 443
        y: 32
        width: 160
        height: 53
        text: qsTr("选择班级")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 40
        verticalAlignment: Text.AlignVCenter
        font.family: "Source Han Sans CN"
    }

    Rectangle {
        id: rectangle6
        x: 32
        y: 113
        width: 54
        height: 43
        color: "#ffffff"
        Text {
            id: element17
            text: "当前"
            topPadding: -3
            font.family: "Source Han Sans CN"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 32
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouseArea8
            anchors.fill: parent
        }
    }

    Rectangle {
        id: rectangle9
        x: 128
        y: 113
        width: 54
        height: 43
        color: "#ffffff"
        Text {
            id: element18
            text: "过去"
            topPadding: -3
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 32
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }

        MouseArea {
            id: mouseArea9
            anchors.fill: parent
        }
    }

ListView {
    id: listView
    spacing: 12
    anchors.right: parent.right
    anchors.rightMargin: 32
    anchors.left: parent.left
    anchors.leftMargin: 32
    anchors.bottom: parent.bottom
    anchors.top: rectangle6.bottom
    anchors.topMargin: 24
    delegate: classListItem

    model: ListModel {
        ListElement {
            name: "2020级计卓"
            time:"周五下午"
            address:"3区1-507"
            number:"30"
        }

        ListElement {
            name: "2020级计卓"
            time:"周五下午"
            address:"3区1-507"
            number:"30"
        }

        ListElement {
            name: "2020级计卓"
            time:"周五下午"
            address:"3区1-507"
            number:"30"
        }
        ListElement {
            name: "2020级计卓"
            time:"周五下午"
            address:"3区1-507"
            number:"30"
        }
    }
}

Component{
    id: classListItem

    Rectangle {
        x: 32
        y: 176
        width: 982
        height: 80
        color: "#f5f5f5"
        radius: 10
        Text {
            id: nameOfClass
            x: 16
            y: 9
            height: 37
            text: name
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 28
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }

        Text {
            id: detail
            x: 16
            y: 44
            height: 27
            color: "#8f8f8f"
            text: time+"·"+address+"·"+number+"人"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 20
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
        }

        MouseArea {
            id: mouseArea10
            anchors.fill: parent
            onClicked: markPage.push(scoreOfClass)
        }
    }
}

    }
    Component{
        id:scoreOfClass
        ScoreWithClass{}
    }

}
/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
