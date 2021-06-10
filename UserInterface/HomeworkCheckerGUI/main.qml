import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import Account 1.0

Window {
    id: window
    width: 1366
    height: 768
    minimumWidth: 960
    minimumHeight: 400
    visible: true
    title: qsTr("Homework Checker")
    property string assignmentId: ""

    Account {
        id: account
    }

    Popup {
        id: logInPopup
        modal: true
        width: 400
        height: 378
        visible: false
        anchors.centerIn: Overlay.overlay
        closePolicy: Popup.NoAutoClose
        contentItem: LoginPage {
            id: loginPage
            anchors.centerIn: parent
            anchors.fill: parent
        }
        background: Rectangle {
            anchors.fill: parent
            clip: true
            radius: 20
            color: "white"
        }
    }

    Popup {
        id: regPopup
        modal: true
        width: 400
        height: 500
        anchors.centerIn: Overlay.overlay
        closePolicy: Popup.NoAutoClose
        contentItem: RegPage {
            id: regPage
            anchors.centerIn: parent
            anchors.fill: parent
        }
        background: Rectangle {
            anchors.fill: parent
            clip: true
            radius: 20
            color: "white"
        }
    }

    Row {
        id: splitView
        visible: true
        anchors.fill: parent
        Column {
            id: naviList
            Layout.preferredWidth: 320
            height: splitView.height
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
                font.family: "Source Han Sans CN"
                font.weight: Font.Medium
                font.pixelSize: 40
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
                    textFormat: Text.PlainText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    verticalAlignment: Text.AlignVCenter
                    font.weight: Font.Medium
                    font.family: "Source Han Sans CN"
                    font.pixelSize: 24
                    color: naviList.index == 0 ? "white" : "black"
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

                        generalPage.refresh();
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
                    font.weight: Font.Medium
                    textFormat: Text.PlainText
                    font.family: "Source Han Sans CN"
                    font.pixelSize: 24
                    color: naviList.index == 1 ? "white" : "black"
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
                        classPage.refresh()
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
                    font.weight: Font.Medium
                    textFormat: Text.PlainText
                    font.family: "Source Han Sans CN"
                    font.pixelSize: 24
                    color: naviList.index == 2 ? "white" : "black"
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

                        taskPage.refresh()
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
                    font.weight: Font.Medium
                    textFormat: Text.PlainText
                    font.family: "Source Han Sans CN"
                    font.pixelSize: 24
                    color: naviList.index == 3 ? "white" : "black"
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
                        markPage.initialItem.refresh()
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
                    font.weight: Font.Medium
                    textFormat: Text.PlainText
                    font.family: "Source Han Sans CN"
                    font.pixelSize: 24
                    color: naviList.index == 4 ? "white" : "black"
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

        GeneralPage {
            id: generalPage
            visible: false
            width: window.width - naviList.width
            height: window.height
        }

        ClassPage {
            id: classPage
            visible: false
            width: window.width - naviList.width
            height: window.height
        }

        TaskPage {
            id: taskPage
            visible: false
            width: window.width - naviList.width
            height: window.height
        }

        MarkPage {
            id: markPage
            visible: false
            width: window.width - naviList.width
            height: window.height
        }

        SettingPage {
            id: settingPage
            visible: false
            width: window.width - naviList.width
            height: window.height
        }

    }

    Timer {id: timer}
    function setTimeout(cb,delayTime) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();
    }

    LaunchScreen {
        id: launchScreen
        visible: true
        property bool loading: true
        Component.onCompleted: {
            account.connectDB()
            setTimeout(() => { loading = false }, 500)
            setTimeout(() => { logInPopup.visible = true }, 1500)
        }
    }

}
