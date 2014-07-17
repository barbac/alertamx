import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    id: root
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

    Progressbar {
        id: progressbar
        width: parent.width
        progress: {
            typeof feedProgress !== 'undefined' ?
                       feedProgress : timerLoader.item
        }
        targetItem: alerts
        text: qsTr('CONAGUA server')
    }

    ListView {
        id: alerts
        opacity: 0
        spacing: 5
        anchors.fill: parent
        model: alertsModel
        delegate: Rectangle {
            width: parent.width
            color: 'lightskyblue'
            height: eventLabel.implicitHeight + 10
            Text {
                id: eventLabel
                text: alert.info.event
                x: 10
                width: alerts.width - 10
                wrapMode: Text.Wrap
                anchors.centerIn: parent
            }
        }
    }
}
