import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import HomeworkInfoVC 1.0

Rectangle {
    id: correctHomework
    x: 0
    y: 0
    width: 1046
    height: 768
    color: "#ffffff"
    radius: 10
    border.width: 1
    border.color: "#00000000"

    property string homeworkId;
    property string contentText;

    property string comment;
    property string score;

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
    }

    function submit() {
        homeworkInfoVC.submit(comment,score)
    }

    Rectangle {
        id: homeworkOfStudents
        y: 203
        width: 748
        height: 540
        color: "#ffffff"
        radius: 1
        border.width: 1
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter

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
            horizontalAlignment: Text.AlignRight
            anchors.fill: parent
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
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
        x: 808
        y: 114
        width: 56
        height: 28
        text: qsTr("附件")
        font.bold: false
        font.weight: Font.Medium
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 28
    }

    ListView {
            id: listView
            x: 0
            y: 148
            height: 506
            //width: 982
            //height: 456
            clip: true
            spacing: 8
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: classHere.bottom
            anchors.topMargin: 24
            anchors.rightMargin: 40
            anchors.leftMargin: 794
            anchors.bottomMargin: 114
            anchors.bottom: parent.bottom
            delegate: attachmentListItem
            model: attachmentModel
        }

   /*
    Rectangle {
        id: addition
        x: 808
        y: 163
        width: 198
        height: 70
        color: "#f5f5f5"
        radius: 10

        Text {
            id: element4
            text: qsTr("6-28.cpp")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.fill: parent
            font.pixelSize: 28
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked:
                taskPage.push(detailOfAddition)
        }
    }
    */
    //ComponentBegein
       Component{

           id: attachmentListItem
           Rectangle {
               id: rectangle1
               //x: 808
               //y: 163
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
                   font.bold: false
                   font.family: "Source Han Sans CN"
                   font.pixelSize: 20
               }

               MouseArea {
                   id: mouseArea1
                   anchors.fill: parent
                   onClicked:
                   {
                       //var item=taskPage.push(detailOfAddition)
                       homeworkInfoVC.downloadFile(fileName)
                       Qt.openUrlExternally(homeworkInfoVC.getWorkPath()+"/"+fileName)
                   }

               }
           }

       }
       //endComponent

    Rectangle {
        id: lastStudent
        x: 40
        y: 676
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10

        Text {
            id: element5
            color: "#0098f7"
            text: qsTr("上一个")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea2
            anchors.fill: parent
        }
    }

    Rectangle {
        id: nextStudent
        x: 270
        y: 676
        width: 218
        height: 56
        color: "#f5f5f5"
        radius: 10
        clip: true
        Text {
            id: element6
            color: "#0098f7"
            text: qsTr("下一个")
            font.weight: Font.Medium
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea3
            anchors.fill: parent
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

        Text {
            id: element7
            color: "#ffffff"
            text: qsTr("打分")
            font.weight: Font.Medium
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea4
            anchors.fill: parent
            onClicked:
                taskPage.push(mark)
        }
    }


    Component{
        id:detailOfAddition
        DetailsOfAddition{}
    }
    Component{
        id:mark
        MarkHomework{}
    }
}




















