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
        spacing: 2
        anchors.fill: parent
        model: alertsModel
        delegate: Rectangle {
            width: parent.width
            color: 'azure'
            height: eventLabel.implicitHeight + 10
            Text {
                id: eventLabel
                text: alert.info.headline
                x: 10
                width: alerts.width - 10
                wrapMode: Text.Wrap
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    alertView.visible = true;
                    alerts.visible = false;
                    alertView.alert = alert;
                }
            }
        }
    }

    Rectangle {
        id: alertView
        property QtObject alert
        visible: false
        anchors.fill: parent
        onAlertChanged: {
            if (alertLoader.active)
                alertLoader.item.alertData = alert;
            else
                alertLoader.active = true;
        }
        Rectangle {
            id: backButton
            color: "skyblue"
            width: parent.width
            height: backButtonLabel.height * 3
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    alertView.visible = false;
                    alerts.visible = true;
                }
            }
            Text {
                id: backButtonLabel
                anchors.centerIn: parent
                text: qsTr("< Lista de alertas")
            }
        }
        Loader {
            anchors.fill: parent
            anchors.topMargin: backButton.height
            onLoaded: item.alertData = parent.alert
            active: false
            id: alertLoader
            sourceComponent: Alert{}
        }
    }

}
