import QtQuick 2.2

Rectangle {
    id: root
    width: column.implicitWidth
    height: column.implicitHeight

    Column {
        id: column
        spacing: 10
        width: 400
        Text {
            text: qsTr('Language; ') + infoData.language
        }
        Text {
            text: qsTr('Category: ') + infoData.categoryString
        }
        Text {
            text: qsTr('Event: ') + infoData.event
        }
        Text {
            text: qsTr('Response type: ') + infoData.responseTypeString
        }
        Text {
            text: qsTr('Urgency: ') + infoData.urgencyString
        }
        Text {
            text: qsTr('Severity: ') + infoData.severityString
        }
        Text {
            text: qsTr('Certainty: ') + infoData.certaintyString
        }
        Text {
            text: qsTr('Effective: ') + infoData.effective
        }
        Text {
            text: qsTr('Expires: ') + infoData.expires
        }
        Text {
            width: parent.width
            wrapMode: Text.Wrap
            text: qsTr('Sender name: ') + infoData.senderName
        }
        Text {
            width: parent.width
            wrapMode: Text.Wrap
            text: qsTr('Headline: ') + infoData.headline
        }
        Text {
            width: parent.width
            wrapMode: Text.Wrap
            text: qsTr('Description: ') + infoData.description
        }
        Text {
            text: qsTr('Instruction: ') + infoData.instruction
        }
        Text {
            text: qsTr('Web: ') + infoData.web
        }
        Text {
            text: qsTr('Contact: ') + infoData.contact
        }
    }
}
