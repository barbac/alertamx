import QtQuick 2.2

Rectangle {
    id: root
    width: parent.width
    height: column.implicitHeight

    Column {
        id: column
        spacing: 1
        width: parent.width
        TextInfo {
            label: qsTr('Identifier:')
            value: alertData.identifier
        }
        TextInfo {
            label: qsTr('Sender:')
            value: alertData.sender
        }
        TextInfo {
            label: qsTr('Sent:')
            value: alertData.sent
        }
        TextInfo {
            label: qsTr('Status:')
            value: alertData.statusString
        }
        TextInfo {
            label: qsTr('Message type:')
            value: alertData.msgTypeString
        }
        TextInfo {
            label: qsTr('Scope:')
            value: alertData.scopeString
        }
        TextInfo {
            label: qsTr('Code:')
            value: alertData.code
        }
    }
}
