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
    QString identifier;
    QString sender;
    QString sent;
    Status status;
    MsgType msgType;
    //QString source;
    Scope scope;
    //QString restriction;
    //QString addresses;
    QString code;
    //QString note;
    //QString references;
    //QString incidents;
    //TODO: looks lie this should be a list
    CAPInfo *info = nullptr;
};

#endif // CAPALERT_H
