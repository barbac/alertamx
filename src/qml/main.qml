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

    Column {
        spacing: 20
        anchors.fill: parent
        Alert {
        }
        Info {
        }
    }
}
