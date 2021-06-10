import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle{
    id:dateRectangle
    color: "#00000000"
    border.color: "#00000000"
    property date date
    property var monthsList: [1,2,3,4,5,6,7,8,9,10,11,12]
    property color labelColor: "#f48fb1"
    property var monthS: [1,3,5,7,8,10,12]
    property string year: yearsTumbler.currentItem.text
    property string month: monthsTumbler.currentItem.text
    property string day: daysTumbler.currentItem.text

    Row {
        anchors.fill: parent
        Tumbler {
            id: yearsTumbler
            width:parent.width/3
            height: parent.height
            font.weight: Font.Medium
            wheelEnabled: true
            font.pixelSize: 16
            font.family: "Source Han Sans CN"
            onCurrentItemChanged: {
                var year = currentItem.text
                var month = monthsTumbler.currentIndex+1
                getDays(year,month)
            }

        }
        Label{
            width: 20
            text: "年"
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 16
            font.family: "Source Han Sans CN"
            color: labelColor
        }

        Tumbler {
            id: monthsTumbler
            width:parent.width/3-30
            height: parent.height
            font.weight: Font.Medium
            model: monthsList
            font.pixelSize: 16
            font.family: "Source Han Sans CN"
            onCurrentIndexChanged: {
                var year = yearsTumbler.currentItem.text
                var month = currentIndex+1
                getDays(year,month)
            }
        }
        Label{
            width: 20
            text: "月"
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 16
            font.family: "Source Han Sans CN"
            color: labelColor
        }
        Tumbler {
            id: daysTumbler
            width:parent.width/3-30
            height: parent.height
            font.weight: Font.Medium
            font.pixelSize: 16
            font.family: "Source Han Sans CN"
        }
        Label{
            width: 20
            text: "日"
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 16
            font.family: "Source Han Sans CN"
            color: labelColor
        }
    }

    Component.onCompleted: {
        initialize()
    }

    function initialize(){//初始化控件
        var yearsList=[]
        date = new Date()
        var year = date.getFullYear()
        for(var i=0;i<8;i++){
            var y = year-i
            yearsList.push(y)
        }
        yearsTumbler.model = yearsList
        yearsTumbler.currentIndex = 0
        var month = date.getMonth()
        monthsTumbler.currentIndex = month
        getDays(year,month+1)
        var day = date.getDate()
        daysTumbler.currentIndex = day-1
    }
    function getDays(year,month){//获取当月天数
        if(monthS.indexOf(month)>-1){
            addDays(31)
        }else if(month>2){
            addDays(30)
        }else{
            if(year%4==0){
                addDays(29)
            }else{
                addDays(28)
            }
        }
    }
    function addDays(days){
        var daysList = []
        for(var i=1;i<=days;i++){
            daysList.push(i)
        }
        daysTumbler.model = daysList
    }
}
