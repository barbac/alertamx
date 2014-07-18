import QtQuick 2.2
import QtQuick.Layouts 1.1

Flickable {
    id: root
    property QtObject alertData
    anchors.fill: parent
    contentHeight: column.height
    contentWidth: column.width

    ColumnLayout {
        id: column
        spacing: 1

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
        Info {
            infoData: alertData.info
        }
    }
}
