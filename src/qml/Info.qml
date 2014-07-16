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
            label: qsTr('Language:')
            value: infoData.language
        }
        TextInfo {
            label: qsTr('Category:')
            value: infoData.categoryString
        }
        TextInfo {
            label: qsTr('Event:')
            value: infoData.event
        }
        TextInfo {
            label: qsTr('Response type:')
            value: infoData.responseTypeString
        }
        TextInfo {
            label: qsTr('Urgency:')
            value: infoData.urgencyString
        }
        TextInfo {
            label: qsTr('Severity:')
            value: infoData.severityString
        }
        TextInfo {
            label: qsTr('Certainty:')
            value: infoData.certaintyString
        }
        TextInfo {
            label: qsTr('Effective:')
            value: infoData.effective
        }
        TextInfo {
            label: qsTr('Expires:')
            value: infoData.expires
        }
        TextInfo {
            label: qsTr('Sender name:')
            value: infoData.senderName
        }
        TextInfo {
            label: qsTr('Headline:')
            value: infoData.headline
        }
        TextInfo {
            label: qsTr('Description:')
            value: infoData.description
        }
        TextInfo {
            label: qsTr('Instruction:')
            value: infoData.instruction
        }
        TextInfo {
            label: qsTr('Web:')
            value: infoData.web
        }
        TextInfo {
            label: qsTr('Contact:')
            value: infoData.contact
        }
        TextInfo {
            label: qsTr('Area:')
            value: infoData.areaDesc
        }
        TextInfo {
            label: qsTr('Area:')
            value: infoData.areaValue
        }
    }
}
