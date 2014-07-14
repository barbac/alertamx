#pragma once

#include <QObject>
#include <QString>

class CAPInfo;

class StatusGadget {
    Q_GADGET
    Q_ENUMS(Status)

public:
    enum class Status {
        Actual,
        Exercise,
        System,
        Test,
        Draft
    };
};
typedef StatusGadget::Status Status;

class MsgTypeGadget {
    Q_GADGET
    Q_ENUMS(MsgType)

public:
    enum class MsgType {
        Alert,
        Update,
        Cancel,
        Ack,
        Error
    };
};
typedef MsgTypeGadget::MsgType MsgType;

class ScopeGadget {
    Q_GADGET
    Q_ENUMS(Scope)

public:
    enum class Scope {
        Public,
        Restricted,
        Private
    };
};
typedef ScopeGadget::Scope Scope;

class CAPAlert: public QObject
{
    //For unit tests
    friend class TestParser;
    Q_OBJECT

    Q_PROPERTY(QString identifier NOTIFY identifierChanged MEMBER m_identifier)
    Q_PROPERTY(QString sender NOTIFY senderChanged MEMBER m_sender)
    Q_PROPERTY(QString sent NOTIFY sentChanged MEMBER m_sent)
    Q_PROPERTY(Status status NOTIFY statusChanged READ status WRITE setStatus)
    Q_PROPERTY(QString statusString READ statusString
               NOTIFY statusStringChanged)
    Q_PROPERTY(MsgType msgType NOTIFY msgTypeChanged READ msgType
               WRITE setMsgType)
    Q_PROPERTY(QString msgTypeString READ msgTypeString
               NOTIFY msgTypeStringChanged)
    //Q_PROPERTY(QString source NOTIFY sourceChanged MEMBER m_source)
    Q_PROPERTY(Scope scope READ scope WRITE setScope NOTIFY scopeChanged)
    Q_PROPERTY(QString scopeString READ scopeString
               NOTIFY scopeStringChanged)
    //Q_PROPERTY(QString restriction NOTIFY restrictionChanged MEMBER m_restriction)
    //Q_PROPERTY(QString addresses NOTIFY addressesChanged MEMBER m_addresses)
    Q_PROPERTY(QString code NOTIFY codeChanged MEMBER m_code)
    //Q_PROPERTY(QString note NOTIFY noteChanged MEMBER m_note)
    //Q_PROPERTY(QString references NOTIFY referencesChanged MEMBER m_references)
    //Q_PROPERTY(QString incidents NOTIFY incidentsChanged MEMBER m_incidents)
    Q_PROPERTY(CAPInfo * info NOTIFY infoChanged MEMBER m_info)

signals:
    void identifierChanged();
    void senderChanged();
    void sentChanged();
    void statusChanged(Status);
    void statusStringChanged(QString);
    void msgTypeChanged(MsgType);
    void msgTypeStringChanged(QString);
    //void sourceChanged();
    void scopeChanged(Scope);
    void scopeStringChanged(QString);
    //void restrictionChanged();
    //void addressesChanged();
    void codeChanged();
    //void noteChanged();
    //void referencesChanged();
    //void incidentsChanged();
    void infoChanged();

public slots:
    void setStatus(Status status);
    void setMsgType(MsgType msgType);
    void setScope(Scope scope);

public:
    explicit CAPAlert(QObject *parent);
    Status status() const;
    QString statusString() const;
    MsgType msgType() const;
    QString msgTypeString() const;
    Scope scope() const;
    QString scopeString() const;

    CAPInfo *m_info = nullptr;

private:
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
};
