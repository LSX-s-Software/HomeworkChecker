import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.1
import ClassScoreVC 1.0

Rectangle {
    id: scoreWithClass
    width: 1046
    height: 768
    color: "#ffffff"

    ClassScoreVC {
        id: classScoreVC
    }

    ListModel {
        id: scoreListModel
    }

    property int classId: -1
    property string className: "加载中"

    Timer {id: timer}
    function setTimeout(cb,delayTime) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();
    }

    function loadData() {
        classScoreVC.getData(classId)
        scoreListModel.clear()
        highest.text = classScoreVC.highestScore.toFixed(2)
        average.text = classScoreVC.avgScore.toFixed(2)
        lowest.text = classScoreVC.lowestScore.toFixed(2)
        classScoreVC.scoreList.forEach(ele => {
                                      scoreListModel.append(ele)
                                  })
    }

    //Component
    Component{
        id: studentListItem
        Rectangle {
            width: listView.width
            height: 62
            color: "#f5f5f5"

            Text {
                id: nameAndNumber
                text: name+"("+schoolNum+")"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 16
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 28
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    let scorePage = markPage.push(scoreOfEach)
                    scorePage.classId = classId
                    scorePage.stuId = classScoreVC.scoreList[index].stuId
                    scorePage.stuName = classScoreVC.scoreList[index].name
                    scorePage.loadData()
                }
            }

            Text {
                id: scoreOfStudent
                width: 45
                text: score
                anchors.right: parent.right
                anchors.rightMargin: 45
                horizontalAlignment: Text.AlignRight
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
        width: 76
        height: 28
        color: "#ffffff"
        anchors.verticalCenter: title.verticalCenter
        anchors.leftMargin: 28
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
            onClicked: {
                classId = -1
                className = "加载中"
                markPage.pop()
            }
        }

        Image {
            id: image1
            width: 25
            height: 22
            source: "images/backBtn.png"
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Text {
        id: title
        height: 40
        text: className
        verticalAlignment: Text.AlignVCenter
        font.family: "Source Han Sans CN"
        font.weight: Font.Medium
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40
    }

    FileDialog {
        id: fileDialog
        currentFile: StandardPaths.writableLocation(StandardPaths.DocumentsLocation) + "/" + className + "成绩.csv"
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        fileMode: FileDialog.SaveFile
        defaultSuffix: "csv"
        onAccepted: {
            console.log(fileDialog.file)
            let result = classScoreVC.exportData(String(fileDialog.file).substring(7))
            if (result) {
                exportBtnText.text = "✓"
            } else {
                exportBtnText.text = "导出失败"
            }
            setTimeout(() => { exportBtnText.text = "导出成绩" }, 1500)
        }
    }

    Rectangle {
        id: rectangle1
        y: 39
        width: 110
        height: 42
        color: "#0098f7"
        radius: 10
        anchors.verticalCenter: title.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 32

        Text {
            id: exportBtnText
            color: "#ffffff"
            text: qsTr("导出成绩")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 20
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                fileDialog.open()
            }
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
            text: "加载中"
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
            text: "加载中"
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
        anchors.top: averageScore.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 32
        anchors.leftMargin: 32
        anchors.topMargin: 22
        delegate: studentListItem
        clip: true
        model: scoreListModel
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
            text: "加载中"
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
        ScoreWithStudent {
            width: markPage.width
            height: markPage.height
        }
    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:14}D{i:23}
}
##^##*/
