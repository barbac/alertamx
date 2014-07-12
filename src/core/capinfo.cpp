#include <QDebug>

#include "capinfo.h"

CAPInfo::CAPInfo(QObject *parent) :
    QObject(parent)
{
}

void CAPInfo::setCategory(Category category)
{
    if (m_category != category) {
        m_category = category;
        emit categoryChanged(category);
    }
}

void CAPInfo::setResponseType(ResponseType responseType)
{
    if (m_responseType != responseType) {
        m_responseType = responseType;
        emit responseTypeChanged(responseType);
    }
}

Category CAPInfo::category() const
{
    return m_category;
}

QString CAPInfo::categoryString() const
{
    switch (m_category) {
    case Category::Geo:
        return tr("Geo");
    case Category::Met:
        return tr("Met");
    case Category::Safety:
        return tr("Safety");
    case Category::Security:
        return tr("Security");
    case Category::Rescue:
        return tr("Rescue");
    case Category::Fire:
        return tr("Fire");
    case Category::Health:
        return tr("Health");
    case Category::Env:
        return tr("Environmental");
    case Category::Transport:
        return tr("Transport");
    case Category::Infra:
        return tr("Infrastructure");
    case Category::CBRNE:
        return tr("CBRNE");
    case Category::Other:
        return tr("Other");
    default:
        qWarning() << "Invalid \"Category\" value";
        return "";
    }
}

ResponseType CAPInfo::responseType() const
{
    return m_responseType;
}

QString CAPInfo::responseTypeString() const
{
    switch (m_responseType) {
    case ResponseType::Shelter:
        return tr("Shelter");
    case ResponseType::Evacuate:
        return tr("Evacuate");
    case ResponseType::Prepare:
        return tr("Prepare");
    case ResponseType::Execute:
        return tr("Execute");
    case ResponseType::Avoid:
        return tr("Avoid");
    case ResponseType::Monitor:
        return tr("Monitor");
    case ResponseType::Assess:
        return tr("Assess");
    case ResponseType::AllClear:
        return tr("AllClear");
    case ResponseType::None:
        return tr("None");
    default:
        qWarning() << "Invalid \"ResponseType\" value";
        return "";
    }
}
