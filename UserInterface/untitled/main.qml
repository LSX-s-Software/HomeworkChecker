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
                        generalPage.visible=true;
                        classPage.visible=false;
                        taskPage.visible=false;
                        markPage.visible=false;
                        settingPage.visible=false;
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
                        generalPage.visible=false;
                        taskPage.visible=false;
                        classPage.visible=true;
                        markPage.visible=false;
                        settingPage.visible=false;

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
                        generalPage.visible=false;
                        taskPage.visible=true;
                        classPage.visible=false;
                        markPage.visible=false;
                        settingPage.visible=false;

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
                    onClicked: {
                        parent.color="#0098f7";
                        naviBtn0.color="white";
                        naviBtn1.color="white";
                        naviBtn2.color="white";
                        naviBtn4.color="white";
                        generalPage.visible=false;
                        taskPage.visible=false;
                        classPage.visible=false;
                        markPage.visible=true;
                        settingPage.visible=false;

                        naviList.index = 3;
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
                    onClicked: {
                        parent.color="#0098f7";
                        naviBtn0.color="white";
                        naviBtn1.color="white";
                        naviBtn2.color="white";
                        naviBtn3.color="white";
                        generalPage.visible=false;
                        taskPage.visible=false;
                        classPage.visible=false;
                        markPage.visible=false;
                        settingPage.visible=true;

                        naviList.index = 4;
                    }
                }
            }
        }

        Rectangle {
            id: generalPage
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

                Text {
                    id: element7
                    x: 87
                    y: 25
                    width: 64
                    height: 43
                    text: qsTr("作业")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 32
                }

                Text {
                    id: element8
                    x: 20
                    y: 139
                    width: 108
                    height: 27
                    text: qsTr("已批改/总数")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                }

                Text {
                    id: element9
                    x: 172
                    y: 143
                    width: 108
                    height: 27
                    text: qsTr("已提交/总数")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
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

                Text {
                    id: element10
                    x: 87
                    y: 25
                    width: 128
                    height: 43
                    text: qsTr("批改进度")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 32
                    verticalAlignment: Text.AlignVCenter
                }

                Text {
                    id: element11
                    x: 96
                    y: 139
                    width: 108
                    height: 27
                    text: qsTr("已批改/总数")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Text {
                id: element6
                x: 379
                y: 353
                width: 288
                height: 48
                text: "早上好！张三老师"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 36
            }
        }

        Rectangle {
            id: classPage
            x: 320
            width: 1046
            height: 768
            color: "#ffffff"
            visible: false

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

            Rectangle {
                id: rectangle
                x: 32
                y: 176
                width: 982
                height: 80
                color: "#f5f5f5"

                Text {
                    id: element12
                    x: 16
                    y: 9
                    width: 144
                    height: 37
                    text: qsTr("2020级计卓")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 28
                }

                Text {
                    id: element13
                    x: 16
                    y: 44
                    width: 234
                    height: 27
                    text: qsTr("周五下午·3区1-507·30人")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                }

                MouseArea {
                    id: mouseArea6
                    anchors.fill: parent
                }
            }

            Image {
                id: image
                x: 954
                y: 676
                width: 60
                height: 60
                visible: true
                source: "Images/addBtn.png"

                MouseArea {
                    id: mouseArea16
                    anchors.fill: parent
                    onClicked: {
                    newAClass.visible=true;
                    }
                }
            }

            Rectangle {
                id: newAClass
                width: 720
                height: 461
                color: "#ffffff"
                visible: false
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                Text {
                    id: element28
                    y: 49
                    width: 128
                    height: 43
                    text: qsTr("创建班级")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 32
                }

                Rectangle {
                    id: rectangle16
                    x: 52
                    y: 103
                    width: 258
                    height: 37
                    color: "#f5f5f5"

                    Text {
                        id: element29
                        width: 48
                        height: 32
                        text: qsTr("名称")
                        anchors.left: parent.horizontalCenter
                        anchors.leftMargin: -129
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 24
                    }

                    Text {
                        id: element30
                        x: 129
                        width: 124
                        height: 32
                        text: qsTr("2020级计卓")
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 24
                    }
                }

                Rectangle {
                    id: rectangle17
                    x: 410
                    y: 103
                    width: 258
                    height: 37
                    color: "#f5f5f5"
                    Text {
                        id: element31
                        width: 96
                        height: 32
                        text: qsTr("上课时间")
                        anchors.left: parent.horizontalCenter
                        anchors.leftMargin: -129
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 24
                    }

                    Text {
                        id: element32
                        x: 129
                        width: 96
                        height: 32
                        text: qsTr("周五下午")
                        anchors.right: parent.right
                        anchors.top: parent.top
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 24
                    }
                }

                Rectangle {
                    id: rectangle18
                    x: 52
                    y: 160
                    width: 258
                    height: 37
                    color: "#f5f5f5"
                    Text {
                        id: element33
                        width: 96
                        height: 32
                        text: qsTr("上课地点")
                        anchors.left: parent.horizontalCenter
                        anchors.leftMargin: -129
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 24
                    }

                    Text {
                        id: element34
                        x: 129
                        width: 98
                        height: 32
                        text: qsTr("3区1-507")
                        anchors.right: parent.right
                        anchors.top: parent.top
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 24
                    }
                }

                Rectangle {
                    id: rectangle19
                    x: 52
                    y: 229
                    width: 616
                    height: 100
                    color: "#f5f5f5"

                    Text {
                        id: element35
                        width: 84
                        height: 37
                        text: qsTr("邀请码")
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 28
                    }

                    Text {
                        id: element36
                        x: 311
                        y: 22
                        width: 94
                        height: 53
                        text: qsTr("CDE2")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 40
                    }
                }

                Rectangle {
                    id: rectangle20
                    x: -131
                    y: 389
                    width: 218
                    height: 56
                    radius: 10;
                    color: "#0098f7"
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: element37
                        y: 11
                        height: 32
                        color: "#ffffff"
                        text: qsTr("创建")
                        anchors.horizontalCenter: parent.horizontalCenter
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 24
                    }

                    MouseArea {
                        id: mouseArea18
                        anchors.fill: parent
                    }
                }

                Image {
                    id: image1
                    x: 655
                    y: 20
                    width: 45
                    height: 45
                    source: "Images/close.png"

                    MouseArea {
                        id: mouseArea17
                        anchors.fill: parent
                        onClicked: {
                        newAClass.visible=false;
                        }
                    }
                }
            }


        }

        Rectangle {
            id: taskPage
            x: 320
            width: 1046
            height: 768
            color: "#ffffff"
            border.width: 0
            visible: false

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

            Rectangle {
                id: rectangle3
                x: 32
                y: 176
                width: 982
                height: 80
                color: "#f5f5f5"
                Text {
                    id: element14
                    x: 16
                    y: 9
                    width: 127
                    height: 37
                    text: qsTr("第六章作业")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 28
                    verticalAlignment: Text.AlignVCenter
                }

                Text {
                    id: element15
                    x: 16
                    y: 45
                    width: 389
                    height: 27
                    text: qsTr("截止于2021年5月15日·已提交 25·未提交 5")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea7
                    anchors.fill: parent
                }
            }
        }

        Rectangle {
            id: markPage
            width: 1046
            height: 768
            color: "#ffffff"
            visible: false

            Text {
                id: element16
                x: 443
                y: 32
                width: 160
                height: 53
                text: qsTr("选择班级")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
                verticalAlignment: Text.AlignVCenter
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
                    font.family: "SimSun"
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 32
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
                    font.pixelSize: 32
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea9
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: rectangle10
                x: 32
                y: 176
                width: 982
                height: 80
                color: "#f5f5f5"
                Text {
                    id: element19
                    x: 16
                    y: 9
                    width: 144
                    height: 37
                    text: qsTr("2020级计卓")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 28
                    verticalAlignment: Text.AlignVCenter
                }

                Text {
                    id: element20
                    x: 16
                    y: 44
                    width: 234
                    height: 27
                    text: qsTr("周五下午·3区1-507·30人")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea10
                    anchors.fill: parent
                }
            }
        }

        Rectangle {
            id: settingPage
            width: 1046
            height: 768
            color: "#ffffff"
            visible: false

            Text {
                id: element21
                x: 483
                y: 32
                width: 80
                height: 53
                text: qsTr("设置")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
                verticalAlignment: Text.AlignVCenter
            }

            Rectangle {
                id: rectangle11
                x: 32
                y: 113
                width: 160
                height: 43
                color: "#ffffff"
                Text {
                    id: element24
                    text: "下载文件夹"
                    topPadding: -3
                    font.family: "SimSun"
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 32
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea11
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: rectangle12
                x: 224
                y: 113
                width: 128
                height: 43
                color: "#ffffff"
                Text {
                    id: element25
                    text: "邮箱配置"
                    topPadding: -3
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 32
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea12
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: rectangle13
                x: 32
                y: 176
                width: 982
                height: 80
                color: "#f5f5f5"
                Text {
                    id: element22
                    x: 16
                    y: 9
                    width: 168
                    height: 37
                    text: qsTr("附件下载目录")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 28
                    verticalAlignment: Text.AlignVCenter
                }

                Text {
                    id: element23
                    x: 16
                    y: 44
                    width: 166
                    height: 27
                    text: qsTr("D:\\Download\\CPP")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea13
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: rectangle14
                x: 32
                y: 272
                width: 218
                height: 56
                color: "#f5f5f5"

                Text {
                    id: element26
                    text: qsTr("修改")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    font.pixelSize: 24
                }

                MouseArea {
                    id: mouseArea14
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: rectangle15
                x: 266
                y: 272
                width: 218
                height: 56
                color: "#f5f5f5"
                Text {
                    id: element27
                    text: qsTr("清空")
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 24
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea15
                    anchors.fill: parent
                }
            }
        }

    }



}















































































/*##^## Designer {
    D{i:43;anchors_height:100;anchors_width:100}D{i:45;anchors_height:100;anchors_width:100}
D{i:50;anchors_height:32;anchors_width:124;anchors_x:129;anchors_y:5}D{i:53;anchors_height:32;anchors_width:124;anchors_x:129;anchors_y:5}
D{i:56;anchors_height:32;anchors_width:124;anchors_x:129;anchors_y:5}D{i:62;anchors_height:100;anchors_width:100}
D{i:64;anchors_height:100;anchors_width:100}D{i:76;anchors_height:100;anchors_width:100}
D{i:88;anchors_height:100;anchors_width:100}D{i:100;anchors_height:100;anchors_width:100}
D{i:103;anchors_height:100;anchors_width:100}D{i:106;anchors_height:100;anchors_width:100}
}
 ##^##*/
