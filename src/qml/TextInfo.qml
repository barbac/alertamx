import QtQuick 2.2
import QtQuick.Layouts 1.1

Rectangle {
    property alias label: label.text
    property alias value: text.text

    id: root
    width: parent.width
    height: row.implicitHeight + 15
    color: 'ghostwhite'

    RowLayout {
        id: row
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        Text {
            id: label
            font.bold: true
            anchors.top: parent.top
        }
        Text {
            id: text
            wrapMode: Text.Wrap
            Layout.fillWidth: true
        }
    }
}
