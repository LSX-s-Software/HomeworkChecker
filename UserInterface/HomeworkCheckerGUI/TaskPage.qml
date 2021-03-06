import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import AssignmentVC 1.0


StackView {
    width: 1046
    height: 768
    clip: true
    id: taskPage
    AssignmentVC {
        id:assignmentVC
    }


    ListModel {
    id: assignmentListModel
    }

    ListModel {
    id: assignmentFinishListModel
    }

    function refresh() {
        assignmentListModel.clear()
        assignmentFinishListModel.clear()
        assignmentVC.refresh()
        assignmentVC.assignmentList.forEach(ele => {
                                                if (ele.finish==="1")
                                                assignmentFinishListModel.append(ele)
                                                else
                                                assignmentListModel.append(ele)
                                            })
    }


    initialItem: Rectangle {

        width: taskPage.width
        height: taskPage.height

        Text {
            id: element3
            y: 32
            width: 240
            height: 53
            text: qsTr("已布置的作业")
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Medium
            font.family: "Source Han Sans CN"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 40
        }

        Rectangle {
            id: rectangle7
            width: 96
            height: 43
            color: "#ffffff"
            anchors.left: parent.left
            anchors.top: element3.bottom
            anchors.topMargin: 28
            anchors.leftMargin: 32

            Text {
                id: element4
                color: "#0098f7"
                text: qsTr("待批改")
                verticalAlignment: Text.AlignVCenter
                font.weight: Font.Medium
                font.family: "Source Han Sans CN"
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 32
            }

            MouseArea {
                id: mouseArea4
                anchors.fill: parent
                onClicked: {
                    element4.color="#0098f7"
                    element5.color="#707070"
                    listView.model=assignmentListModel
                }
            }
        }

        Rectangle {
            id: rectangle8
            width: 160
            height: 43
            color: "#ffffff"
            anchors.left: rectangle7.right
            anchors.top: element3.bottom
            anchors.topMargin: 28
            anchors.leftMargin: 32

            Text {
                id: element5
                color: "#707070"
                text: qsTr("已完成批改")
                verticalAlignment: Text.AlignVCenter
                font.weight: Font.Medium
                font.family: "Source Han Sans CN"
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 32
            }

            MouseArea {
                id: mouseArea5
                anchors.fill: parent
                onClicked: {
                    element4.color="#707070"
                    element5.color="#0098f7"
                    listView.model=assignmentFinishListModel
                }
            }
        }

        Component {
            id: homeworkListItem

            Rectangle {
                width: listView.width
                height: 80
                color: "#f5f5f5"
                radius: 10
                Text {
                    id: element14
                    x: 16
                    y: 9
                    height: 37
                    text: name
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 28
                    verticalAlignment: Text.AlignVCenter
                    font.family: "Source Han Sans CN"
                }

                Text {
                    id: element15
                    x: 16
                    y: 45
                    height: 27
                    color: "#8f8f8f"
                    text: "截止于" + deadline+ "·已提交 " + submitted + "·未提交 " + notSubmitted
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    font.family: "Source Han Sans CN"
                }

                MouseArea {
                    id: mouseArea7
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        window.assignmentId=id;
                        //console.log(window.assignmentId)
                        let item=taskPage.push(info)
                        item.refresh()
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
            clip: true
            spacing: 12
            anchors.topMargin: 24
            anchors.bottomMargin: 0
            anchors.rightMargin: 32
            anchors.leftMargin: 32
            delegate: homeworkListItem
            model: assignmentListModel
        }

        Image {
            id: addBtn
            width: 60
            height: 60
            visible: true
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            source: "images/add@2x.png"
            anchors.bottomMargin: 28
            anchors.rightMargin: 32

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    newAssignment.show()
                }
            }
        }

        Component {
            id: info
            InfoOfTask {
                width: taskPage.width
                height: taskPage.height
            }
        }

        Popup {
            id: newAssignmentPopup
            modal: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            width: 922
            height: 640
            focus: true
            clip: true
            anchors.centerIn: Overlay.overlay
            background: Rectangle {
                radius: 20
            }
            contentItem: NewAssignment {
                id: newAssignment
                anchors.centerIn: parent
                anchors.fill: parent
            }
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
