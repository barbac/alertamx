#ifndef CAPALERT_H
#define CAPALERT_H

#include <QObject>
#include <QString>

class CAPInfo;

enum class Status {
    Actual,
    Exercise,
    System,
    Test,
    Draft
};

enum class MsgType {
    Alert,
    Update,
    Cancel,
    Ack,
    Error
};

enum class Scope {
    Public,
    Restricted,
    Private
};

class CAPAlert: public QObject
{
public:
    explicit CAPAlert(QObject *parent);
    QString m_identifier;
    QString m_sender;
    QString m_sent;
    Status m_status;
    MsgType m_msgType;
    //QString m_source;
    Scope m_scope;
    //QString m_restriction;
    //QString m_addresses;
    QString m_code;
    //QString m_note;
    //QString m_references;
    //QString m_incidents;
    //TODO: looks lie this should be a list
    CAPInfo *m_info = nullptr;
};

#endif // CAPALERT_H
