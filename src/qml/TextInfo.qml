import QtQuick 2.2

Rectangle {
    property alias label: label.text
    property alias value: text.text

    id: root
    width: parent.width
    height: text.height + 25
    color: 'ghostwhite'

    Text {
        id: label
        font.bold: true
    }
    Text {
        id: text
        anchors.left: label.right
        anchors.right: parent.right
        anchors.leftMargin: 10
        wrapMode: Text.Wrap
    }
}
