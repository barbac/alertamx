import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    visible: true
    width: 400
    height: 650

    //This one is just for testing
    Loader {
        id: timerLoader
        asynchronous: false
        sourceComponent: {
            if (typeof feedProgress === 'undefined')
                return timerComponent;
        }
        Component {
            id: timerComponent
            Timer {
                property real recieved: 0
                property real total: 100
                signal finished
                signal downloadProgress(real bytesReceived, real bytesTotal)
                repeat: true
                running: true
                onTriggered: {
                    if (recieved >= total) {
                        repeat = false;
                        finished();
                        return;
                    }
                    recieved += 20;
                    downloadProgress(recieved, total);
                }
            }
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
