import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    visible: true
    width: 400
    height: 650

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    ListView {
        anchors.fill: parent
        model: 1
        delegate: Column {
            spacing: 20
            width: parent.width
            height: implicitHeight
            Alert {
            }
            Info {
            }
        }
    }
}
