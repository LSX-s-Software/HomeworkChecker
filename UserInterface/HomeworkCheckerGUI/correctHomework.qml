import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import HomeworkInfoVC 1.0


Rectangle {
    id: correctHomework
    width: 1046
    height: 768
    color: "#ffffff"

    property string homeworkId;
    property string contentText;

    property string comment;
    property string score;
    property string continueId;
    property bool showCommentField: false
    property var continueIdList;
    property int index:-1
    HomeworkInfoVC {
        id:homeworkInfoVC
    }

    ListModel {
        id: attachmentModel
    }

    function refresh() {
        homeworkInfoVC.setHomeworkId(homeworkId)
        attachmentModel.clear()
        homeworkInfoVC.initLoad()
        correctHomework.contentText=homeworkInfoVC.getText()
        homeworkInfoVC.attachmentList.forEach(ele => {
                                          attachmentModel.append(ele)
                                  })
        console.log(continueId)
        correctHomework.continueIdList=continueId.split("|")
        //correctHomework.index=-1
    }

    function submit() {
        homeworkInfoVC.submit(comment,score)
    }

    Rectangle {
        id: homeworkOfStudents
        color: "#ffffff"
        radius: 5
        border.color: "#707070"
        border.width: 1
        anchors.left: parent.left
        anchors.right: listView.left
        anchors.top: element1.bottom
        anchors.bottom: nextStudent.top
        anchors.rightMargin: 20
        anchors.bottomMargin: 22
        anchors.topMargin: 34
        anchors.leftMargin: 40

        TextArea {
            id: textArea
            text: correctHomework.contentText
            anchors.fill: parent
            font.weight: Font.Medium
            font.family: "Source Han Sans CN"
            font.pixelSize: 20
        }
    }

    Text {
        id: element1
        width: 160
        height: 40
        text: qsTr("批改作业")
        font.weight: Font.Medium
        verticalAlignment: Text.AlignVCenter
        font.family: "Source Han Sans CN"
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40
    }

    Rectangle {
        id: backBtn
        width: 76
        height: 28
        color: "#ffffff"
        anchors.top: parent.top
        anchors.topMargin: 46
        anchors.left: parent.left
        anchors.leftMargin: 28

        Text {
            id: element2
            color: "#0098f7"
            text: qsTr("返回")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignRight
            anchors.fill: parent
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                infoOfTask.refresh()
                taskPage.pop()
            }
        }

        Image {
            id: image
            width: 25
            height: 22
            anchors.verticalCenter: parent.verticalCenter
            source: "images/backBtn.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    Text {
        id: element3
        text: qsTr("文件列表")
        anchors.right: parent.right
        anchors.top: homeworkOfStudents.top
        font.weight: Font.Medium
        verticalAlignment: Text.AlignVCenter
        anchors.rightMargin: 126
        anchors.topMargin: 0
        font.family: "Source Han Sans CN"
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 28
    }

    ListView {
            id: listView
            x: 0
            clip: true
            spacing: 8
            anchors.left: element3.left
            anchors.right: parent.right
            anchors.top: element3.bottom
            anchors.topMargin: 20
            anchors.rightMargin: 40
            anchors.leftMargin: 0
            anchors.bottomMargin: 114
            anchors.bottom: parent.bottom
            delegate: attachmentListItem
            model: attachmentModel
        }

    //ComponentBegein
       Component{

           id: attachmentListItem
           Rectangle {
               id: rectangle1
               width: 198
               height: 50
               color: "#f5f5f5"
               radius: 10

               Text {
                   id: element4
                   text: fileName
                   verticalAlignment: Text.AlignVCenter
                   anchors.fill: parent
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.left: parent.left
                   anchors.leftMargin: 8
                   font.family: "Source Han Sans CN"
                   font.pixelSize: 20
                   font.weight: Font.Medium
               }

               MouseArea {
                   id: mouseArea1
                   anchors.fill: parent
                   onClicked: {
                       homeworkInfoVC.downloadFile(fileName)
                       Qt.openUrlExternally(homeworkInfoVC.getWorkPath()+"/"+fileName)
                   }

               }
           }

       }
       //endComponent

    Rectangle {
        id: nextStudent
        visible: !showCommentField
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 36
        anchors.leftMargin: 40
        clip: true
        Text {
            id: element6
            color: "#0098f7"
            text: qsTr("下一个")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea3
            anchors.fill: parent
            onClicked:
            {
                index++
                if(index===continueIdList.length||continueIdList[index]==="")
                {
                    infoOfTask.refresh()
                    taskPage.pop()
                }
                else
                {
                    homeworkId=continueIdList[index]
                    refresh()
                }
            }
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
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 36
        anchors.rightMargin: 40

        Text {
            id: element7
            color: "#ffffff"
            text: qsTr("打分")
            font.weight: Font.Medium
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea4
            anchors.fill: parent
            onClicked: {
                if (!showCommentField) {
                    correctHomework.showCommentField = true
                    element7.text = "提交"
                } else {
                    //提交分数并加载下一份作业
                    correctHomework.comment = commentField.text
                    correctHomework.score = markField.text
                    correctHomework.submit()
                    correctHomework.showCommentField = false
                    element7.text = "打分"
                    index++
                    if(index===continueIdList.length||continueIdList[index]==="")
                    {
                        infoOfTask.refresh()
                        taskPage.pop()
                    }
                    else
                    {
                        homeworkId=continueIdList[index]
                        refresh()
                    }
                }
            }
        }
    }

//    Rectangle {
//        id: runBtn
//        width: 218
//        height: 56
//        color: "#0098f7"
//        radius: 10
//        visible: !showCommentField
//        anchors.bottom: parent.bottom
//        anchors.horizontalCenter: parent.horizontalCenter
//        Text {
//            id: element8
//            color: "#ffffff"
//            text: qsTr("编译并运行")
//            anchors.fill: parent
//            font.pixelSize: 24
//            horizontalAlignment: Text.AlignHCenter
//            verticalAlignment: Text.AlignVCenter
//            font.family: "Source Han Sans CN"
//            font.weight: Font.Medium
//        }

//        MouseArea {
//            id: mouseArea5
//            anchors.fill: parent
//        }
//        anchors.bottomMargin: 36
//    }

    TextField {
        id: commentField
        height: 48
        visible: showCommentField
        anchors.verticalCenter: markBtn.verticalCenter
        anchors.left: parent.left
        anchors.right: markField.left
        anchors.rightMargin: 16
        placeholderTextColor: "#8f8f8f"
        font.pixelSize: 24
        font.family: "Source Han Sans CN"
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 40
        placeholderText: qsTr("评语")
        background: Rectangle {
            anchors.fill: parent
            color: "#F5F5F5"
            radius: 7
            clip: true
        }
    }

    TextField {
        id: markField
        width: 175
        height: 48
        visible: showCommentField
        anchors.verticalCenter: markBtn.verticalCenter
        anchors.right: markBtn.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.weight: Font.Medium
        anchors.rightMargin: 16
        font.pixelSize: 24
        placeholderText: qsTr("分数")
        placeholderTextColor: "#8f8f8f"
        background: Rectangle {
            color: "#f5f5f5"
            radius: 7
            anchors.fill: parent
            clip: true
        }
        font.family: "Source Han Sans CN"
    }
}


