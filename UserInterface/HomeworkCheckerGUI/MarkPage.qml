import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
StackView {
    width: 1046
    height: 768
    clip: true
    id: markPage
    initialItem: ClassPage {
        displayType: 2
        width: markPage.width
        height: markPage.height
    }
}
/*##^##
Designer {
    D{i:0;formeditorZoom:0.75;height:768;width:1046}
}
##^##*/
