import QtQuick 2.2

Rectangle {
    id: root
    width: column.implicitWidth
    height: column.implicitHeight

    Column {
        id: column
        spacing: 10
        Text {
            text: qsTr('Identifier; ') + alertData.identifier
        }
        Text {
            text: qsTr('Sender; ') + alertData.sender
        }
        Text {
            text: qsTr('Sent: ') + alertData.sent
        }
        Text {
            text: qsTr('Status: ') + alertData.statusString
        }
        Text {
            text: qsTr('Message type: ') + alertData.msgTypeString
        }
        Text {
            text: qsTr('Scope: ') + alertData.scopeString
        }
        Text {
            text: qsTr('Code: ') + alertData.code
        }
    }
}
