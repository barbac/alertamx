#include <QDebug>

#include "capalert.h"
#include "capinfo.h"

void CAPAlert::setStatus(Status status)
{
    if (m_status != status) {
        m_status = status;
        emit statusChanged(status);
    }
}

void CAPAlert::setMsgType(MsgType msgType)
{
    if (m_msgType != msgType) {
        m_msgType = msgType;
        emit msgTypeChanged(msgType);
    }
}

void CAPAlert::setScope(Scope scope)
{
    if (m_scope != scope) {
        m_scope = scope;
        emit scopeChanged(scope);
    }
}

CAPAlert::CAPAlert(QObject *parent) :
    QObject(parent)
{
    m_info = new CAPInfo(this);
}

Status CAPAlert::status() const {
    return m_status;
}

QString CAPAlert::statusString() const
{
    switch (m_status) {
    case Status::Actual:
        return tr("Actual");
    case Status::Exercise:
        return tr("Exercise");
    case Status::System:
        return tr("System");
    case Status::Test:
        return tr("Test");
    case Status::Draft:
        return tr("Draft");
    default:
        qWarning() << "Invalid Status value";
        return "";
    }
}

MsgType CAPAlert::msgType() const
{
    return m_msgType;
}

QString CAPAlert::msgTypeString() const
{
    switch (m_msgType) {
    case MsgType::Alert:
        return tr("Alert");
    case MsgType::Update:
        return tr("Update");
    case MsgType::Cancel:
        return tr("Cancel");
    case MsgType::Ack:
        return tr("Acknowledges");
    case MsgType::Error:
        return tr("Error");
    default:
        return "";
    }
}

Scope CAPAlert::scope() const
{
    return m_scope;
}

QString CAPAlert::scopeString() const
{
    switch (m_scope) {
    case Scope::Public:
        return tr("Public");
    case Scope::Restricted:
        return tr("Restricted");
    case Scope::Private:
        return tr("Private");
    default:
        return "";
    }
}
