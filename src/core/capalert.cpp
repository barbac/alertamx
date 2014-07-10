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
