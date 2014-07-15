import QtQuick 2.2

Rectangle {
    id: root
    property var progress
    property Item targetItem
    property alias text: label.text
    border.color: 'skyblue'
    width: label.implicitWidth
    height: label.implicitHeight * 3
    Rectangle {
        id: progressIndicator
        height: parent.height
        color: parent.border.color
        Behavior on width {
            id: widthBehavior
            NumberAnimation {
                duration: 400
            }
        }
        SequentialAnimation {
            id: transition
            NumberAnimation {
                target: progressIndicator
                to: root.width
            }
            OpacityAnimator {
                target: root
                from: 1
                to: 0
                duration: 400
            }
            OpacityAnimator {
                target: targetItem
                from: 0
                to: 1
                duration: 400
            }
        }

        Connections {
            target: progress
            onDownloadProgress: {
                progressIndicator.width = bytesReceived *
                        root.width / bytesTotal;
            }
            onFinished: transition.start()
        }
    }
    Text {
        id: label
        anchors.centerIn: parent
    }
}
