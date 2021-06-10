import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import HomeworkVC 1.0

Rectangle {
    id: infoOfTask
    width: 1046
    height: 768
    color: "#ffffff"

    HomeworkVC {
        id:homeworkVC
    }

    ListModel {
        id: homeworkListModel
    }
    property int uncheckNum: 0
    property int finishNum: 0
    property string assignmentName: ""
    property string deadline: ""
    property string className: ""


    function refresh() {
        homeworkVC.setAssignmentId(window.assignmentId)
        homeworkListModel.clear()
        infoOfTask.deadline=homeworkVC.getDeadline()
        infoOfTask.assignmentName=homeworkVC.getClassName()
        infoOfTask.className=homeworkVC.getClassName()
        homeworkVC.refresh()
        uncheckNum=homeworkVC.getUncheckNum()
        finishNum=homeworkVC.getFinishNum()
        homeworkVC.homeworkList.forEach(ele => {
                                          homeworkListModel.append(ele)
                                  })
    }

    //ComponentBegein
    Component{

        id: studentListItem
        Rectangle {
            id: rectangle1
            width: listView.width
            height: 61
            radius: 10
            color:      (status === 1
                        ? "#b8e4fe"
                        : "#f5f5f5")
            Text {
                id: nameAndNumber
                text: name+"("+studentNum+")"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 16
                font.weight: Font.Medium
                verticalAlignment: Text.AlignVCenter
                font.family: "Source Han Sans CN"
                font.pixelSize: 28
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked:
                {
                    var item=taskPage.push(correctHomework)
                    item.homeworkId=id
                    for (var i=index+1;i!==homeworkListModel.count;i++)
                    {
                        if(homeworkListModel.get(i).status===1)
                        {
                            item.continueId+=(homeworkListModel.get(i).id+"|")
                        }
                    }
                    if(item.continueId!=="")
                    {
                        item.continueId=item.continueId.slice(0,-1)
                    }
                    //console.log(item.homeworkId+" "+item.continueId)
                    item.refresh()
                }

            }

            Text {
                id: scoreOfStudent
                x: 938
                y: 17
                width: 45

                text: (status === 1
                       ? "未批改"
                       : score)
                anchors.right: parent.right
                anchors.rightMargin: 45
                horizontalAlignment: Text.AlignRight
                font.family: "Source Han Sans CN"
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 28
            }

            Image {
                id: image
                x: 974
                y: 17
                width: 9
                height: 28
                anchors.rightMargin: 20
                anchors.right: parent.right
                fillMode: Image.PreserveAspectFit
                source: "images/more.png"
            }
        }
    }
    //endComponent

    Text {
        id: element
        text: assignmentName
        font.weight: Font.Medium
        font.family: "Source Han Sans CN"
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 40
    }

    ListView {
        id: listView
        clip: true
        spacing: 12
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: classHere.bottom
        anchors.topMargin: 24
        anchors.rightMargin: 32
        anchors.leftMargin: 32
        anchors.bottomMargin: 20
        anchors.bottom: progressBar.top
        property int listIndex: currentIndex
        delegate: studentListItem
        model: homeworkListModel
    }

    Rectangle {
        id:classHere
        width: 322
        height: 28
        anchors.leftMargin: 32
        anchors.topMargin: 120
        anchors.left: parent.left
        anchors.top: parent.top
        Text {
            id: element29
            height: 32
            text: qsTr("班级")
            anchors.leftMargin: 0
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
            font.weight: Font.Medium
        }

        Text {
            id: element30
            x: 129
            height: 32
            text: className
            font.family: "Source Han Sans CN"
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
            anchors.top: parent.top
        }
    }

    ProgressBar {
        id: progressBar
        height: 20
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 32
        anchors.leftMargin: 32
        value: finishNum/(uncheckNum+finishNum)
        anchors.bottomMargin: 20
        anchors.bottom: deleteTheTask.top
    }

    Rectangle {
        id: deleteTheTask
        width: 218
        height: 56
        color: "#fa5151"
        radius: 10
        anchors.bottom: parent.bottom
        anchors.horizontalCenterOffset: -140
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20

        Text {
            id: element1
            color: "#ffffff"
            text: qsTr("删除")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea2
            anchors.fill: parent
            onClicked: {
                if (element1.text == "删除") {
                    element1.text = "确认删除"
                } else {
                    if (homeworkVC.deleteAssignment()) {
                        element1.text = "操作成功"
                        taskPage.pop()
                    } else {
                        element1.text = "操作失败"
                    }
                    element1.text = "删除"
                }
            }
        }
    }

    Rectangle {
        id: deadLine
        width: 452
        height: 28
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 32
        anchors.topMargin: 120
        Text {
            id: element31
            height: 32
            text: qsTr("截止时间")
            anchors.leftMargin: 0
            anchors.left: parent.left
            font.family: "Source Han Sans CN"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 24
            font.weight: Font.Medium
        }

        Text {
            id: element32
            x: 129
            height: 32
            text: deadline
            anchors.right: parent.right
            font.family: "Source Han Sans CN"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 24
            anchors.top: parent.top
        }
       // anchors.top: element28.bottom
    }

    Rectangle {
        id: continueCorrect
        width: 218
        height: 56
        color: uncheckNum == 0 ? "#999999" : "#0098f7"
        radius: 10
        anchors.bottom: parent.bottom
        anchors.horizontalCenterOffset: 140
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        Text {
            id: element2
            color: "#ffffff"
            text: "继续批改"
            font.weight: Font.Medium
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            id: mouseArea3
            anchors.fill: parent
            onClicked:
            {
                if (uncheckNum == 0) {
                    return
                }
                if (homeworkListModel.get(0).status === 1)
                {
                    var item=taskPage.push(correctHomework)
                    item.homeworkId=homeworkListModel.get(0).id
                    for (var i=0+1;i!==homeworkListModel.count;i++)
                    {
                        if(homeworkListModel.get(i).status===1)
                        {
                            item.continueId+=(homeworkListModel.get(i).id+"|")
                        }
                    }
                    if(item.continueId!=="")
                    {
                        item.continueId=item.continueId.slice(0,-1)
                    }
                    item.refresh()
                }
            }
        }
    }

    Rectangle {
        id: backBtn
        width: 76
        height: 28
        color: "#ffffff"
        anchors.topMargin: 46
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
                taskPage.pop()
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
        anchors.top: parent.top
    }

    Component
    {
        id:correctHomework
        CorrectHomework {
            width: taskPage.width
            height: taskPage.height
        }
    }



}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:15}
}
##^##*/
