import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: launchScreen
    anchors.fill: parent
    color: "white"
    width: 1366
    height: 768

    Text {
        id: title
        color: "#0098f7"
        text: "Homework Checker"
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.verticalCenterOffset: -60
        font.pointSize: 80
        font.family: "Source Han Sans CN"
        anchors.horizontalCenter: parent.horizontalCenter

    }

    Text {
        id: text1
        x: 497
        text: qsTr("Ultimate Teacher Experience")
        anchors.top: title.bottom
        font.pixelSize: 28
        horizontalAlignment: Text.AlignHCenter
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Source Han Sans CN"
    }

    BusyIndicator {
        id: busyIndicator
        running: loading
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
