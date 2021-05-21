import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: window
    width: 1366
    height: 768
    visible: true
    title: qsTr("Homework Checker")

    Row {
        id: splitView
        visible: true
        anchors.fill: parent
        Column {
            id: naviList
            width: 320
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            rightPadding: 18
            leftPadding: 18
            bottomPadding: 18
            topPadding: 80
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            spacing: 12

            property int index: 0

            Text {
                id: naviTitle
                text: "导航"
                font.bold: true
                font.weight: Font.Medium
                font.pointSize: 40
                textFormat: Text.PlainText
            }

            Rectangle {
                id: naviBtn0
                color: "#0098f7"
                width: 284
                height: 56
                radius: 10
                visible: true
                border.width: 0

                Text {
                    id: naviTxt0
                    text: qsTr("总览")
                    fontSizeMode: Text.Fit
                    elide: Text.ElideLeft
                    textFormat: Text.RichText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 24
                    color: "black"
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    onEntered: {
                        if (naviList.index !== 0) {
                            parent.color = "#0f0098F7"
                        }
                    }
                    onExited: {
                        if (naviList.index !== 0) {
                            parent.color = "white"
                        }
                    }
                    onClicked: {
                        parent.color="#0098f7";
                        naviBtn1.color="white";
                        naviBtn2.color="white";
                        naviBtn3.color="white";
                        naviBtn4.color="white";
                        rectangle.visible=true;
                        rectangle3.visible=false;
                        rectangle6.visible=false;
                        naviList.index = 0;
                    }
                }
            }

            Rectangle {
                id: naviBtn1
                width: 284
                height: 56
                radius: 10
                border.width: 0

                Text {
                    id: naviTxt1
                    text: qsTr("班级")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 24
                    color: "black"
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    onEntered: {
                        if (naviList.index !== 1) {
                            parent.color = "#0f0098f7"
                        }
                    }
                    onExited: {
                        if (naviList.index !== 1) {
                            parent.color = "white"
                        }
                    }
                    onClicked: {
                        parent.color="#0098f7";
                        naviBtn0.color="white";
                        naviBtn2.color="white";
                        naviBtn3.color="white";
                        naviBtn4.color="white";
                        rectangle.visible=false;
                        rectangle3.visible=false;
                        rectangle6.visible=true;
                        naviList.index = 1;
                    }
                }
            }

            Rectangle {
                id: naviBtn2
                width: 284
                height: 56
                radius: 10
                border.width: 0

                Text {
                    id: naviTxt2
                    text: qsTr("作业")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 24
                    color: "black"
                }

                MouseArea {
                    clip: false
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    onEntered: {
                        if (naviList.index !== 2) {
                            parent.color = "#0f0098f7"
                        }
                    }
                    onExited: {
                        if (naviList.index !== 2) {
                            parent.color = "white"
                        }
                    }
                    onClicked: {
                        parent.color="#0098f7";
                        naviBtn0.color="white";
                        naviBtn1.color="white";
                        naviBtn3.color="white";
                        naviBtn4.color="white";
                        rectangle.visible=false;
                        rectangle3.visible=true;
                        rectangle6.visible=false;
                        naviList.index = 2;
                    }
                }
            }

            Rectangle {
                id: naviBtn3
                width: 284
                height: 56
                radius: 10
                border.width: 0

                Text {
                    id: naviTxt3
                    text: qsTr("成绩")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 24
                    color: "black"
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    onEntered: {
                        if (naviList.index !== 3) {
                            parent.color = "#0f0098f7"
                        }
                    }
                    onExited: {
                        if (naviList.index !== 3) {
                            parent.color = "white"
                        }
                    }
                }
            }

            Rectangle {
                id: naviBtn4
                width: 284
                height: 56
                radius: 10
                border.width: 0

                Text {
                    id: naviTxt4
                    text: qsTr("设置")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 24
                    color: "black"
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    onEntered: {
                        if (naviList.index !== 4) {
                            parent.color = "#0f0098f7"
                        }
                    }
                    onExited: {
                        if (naviList.index !== 4) {
                            parent.color = "white"
                        }
                    }
                }
            }
        }

        Rectangle {
            id: rectangle
            x: 320
            width: 1046
            height: 768
            clip: false
            visible: false

            Rectangle {
                width: 202
                height: 200
                radius: 100
                visible: false
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
                    source: "file"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Rectangle {
                id: rectangle1
                x: 173
                y: 533
                width: 300
                height: 185
                color: "#ffffff"

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: rectangle2
                x: 573
                y: 533
                width: 300
                height: 185
                color: "#ffffff"

                MouseArea {
                    id: mouseArea1
                    anchors.fill: parent
                }
            }
        }

        Rectangle {
            id: rectangle3
            x: 320
            width: 1046
            height: 768
            color: "#ffffff"
            visible: true

            Text {
                id: element
                y: 32
                width: 240
                height: 53
                text: qsTr("已创建的班级")
                anchors.horizontalCenter: parent.horizontalCenter
                font.weight: Font.ExtraLight
                font.capitalization: Font.SmallCaps
                font.pixelSize: 40
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideMiddle
                horizontalAlignment: Text.AlignHCenter
            }

            Rectangle {
                id: rectangle4
                x: 32
                y: 113
                width: 54
                height: 43
                color: "#ffffff"

                Text {
                    id: element1
                    text: "当前"
                    topPadding: -3
                    font.family: "SimSun"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    font.pixelSize: 32
                }

                MouseArea {
                    id: mouseArea2
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: rectangle5
                x: 128
                y: 113
                width: 54
                height: 43
                color: "#ffffff"
                Text {
                    id: element2
                    text: "过去"
                    font.pixelSize: 32
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    topPadding: -3
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea3
                    anchors.fill: parent
                }
            }


        }

        Rectangle {
            id: rectangle6
            x: 320
            width: 1046
            height: 768
            color: "#ffffff"
            border.width: 0
            visible: true

            Text {
                id: element3
                y: 32
                width: 240
                height: 53
                text: qsTr("已布置的作业")
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
            }

            Rectangle {
                id: rectangle7
                x: 32
                y: 113
                width: 96
                height: 43
                color: "#ffffff"

                Text {
                    id: element4
                    text: qsTr("待批改")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    font.pixelSize: 32
                }

                MouseArea {
                    id: mouseArea4
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: rectangle8
                x: 160
                y: 113
                width: 160
                height: 43
                color: "#ffffff"

                Text {
                    id: element5
                    text: qsTr("已完成批改")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    font.pixelSize: 32
                }

                MouseArea {
                    id: mouseArea5
                    anchors.fill: parent
                }
            }
        }
    }



}

























/*##^## Designer {
    D{i:23;anchors_height:100;anchors_width:100;anchors_x:47;anchors_y:19}D{i:25;anchors_height:100;anchors_width:100;anchors_x:47;anchors_y:19}
D{i:29;anchors_x:15;anchors_y:8}D{i:30;anchors_height:100;anchors_width:100;anchors_x:80;anchors_y:440}
D{i:32;anchors_x:15;anchors_y:8}D{i:33;anchors_height:100;anchors_width:100;anchors_x:"-16";anchors_y:"-23"}
D{i:37;anchors_x:36;anchors_y:16}D{i:38;anchors_height:100;anchors_width:100}D{i:40;anchors_x:68;anchors_y:16}
D{i:41;anchors_height:100;anchors_width:100}
}
 ##^##*/
