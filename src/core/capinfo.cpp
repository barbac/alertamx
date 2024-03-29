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
        emit categoryStringChanged(categoryString());
    }
}

void CAPInfo::setResponseType(ResponseType responseType)
{
    if (m_responseType != responseType) {
        m_responseType = responseType;
        emit responseTypeChanged(responseType);
        emit responseTypeStringChanged(responseTypeString());
    }
}

void CAPInfo::setUrgency(Urgency urgency)
{
    if (m_urgency != urgency) {
        m_urgency = urgency;
        emit urgencyChanged(urgency);
        emit urgencyStringChanged(urgencyString());
    }
}

void CAPInfo::setSeverity(Severity severity)
{
    if (m_severity != severity) {
        m_severity = severity;
        emit severityChanged(severity);
        emit severityStringChanged(severityString());
    }
}

void CAPInfo::setCertainty(Certainty certainty)
{
    if (m_certainty != certainty) {
        m_certainty = certainty;
        emit certaintyChanged(certainty);
        emit certaintyStringChanged(certaintyString());
    }
}

void CAPInfo::setAreaDesc(QString areaDesc)
{
    if (m_areaDesc != areaDesc) {
        m_areaDesc = areaDesc;
        emit areaDescChanged(areaDesc);
    }
}

void CAPInfo::setAreaValue(QString areaValue)
{
    if (m_areaValue != areaValue) {
        m_areaValue = areaValue;
        emit areaValueChanged(areaValue);
    }
}

void CAPInfo::setAreaType(AreaType areaType)
{
    if (m_areaType != areaType) {
        m_areaType = areaType;
        emit areaTypeChanged(areaType);
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

Urgency CAPInfo::urgency() const
{
    return m_urgency;
}

QString CAPInfo::urgencyString() const
{
    switch (m_urgency) {
    case Urgency::Immediate:
        return tr("Immediate");
    case Urgency::Expected:
        return tr("Expected");
    case Urgency::Future:
        return tr("Future");
    case Urgency::Past:
        return tr("Past");
    case Urgency::Unknown:
        return tr("Unknown");
    default:
        qWarning() << "Invalid \"Urgency\" value";
        return "";
    }
}

Severity CAPInfo::severity() const
{
    return m_severity;
}

QString CAPInfo::severityString() const
{
    switch (m_severity) {
    case Severity::Extreme:
        return tr("Extreme");
    case Severity::Severe:
        return tr("Severe");
    case Severity::Moderate:
        return tr("Moderate");
    case Severity::Minor:
        return tr("Minor");
    case Severity::Unknown:
        return tr("Unknown");
    default:
        return "";
    }
}

Certainty CAPInfo::certainty() const
{
    return m_certainty;
}

QString CAPInfo::certaintyString() const
{
    switch (m_certainty) {
    case Certainty::Observed:
        return tr("Observed");
    case Certainty::Likely:
        return tr("Likely");
    case Certainty::Possible:
        return tr("Possible");
    case Certainty::Unlikely:
        return tr("Unlikely");
    case Certainty::Unknown:
        return tr("Unknown");
    default:
        return "";
    }
}

QString CAPInfo::areaDesc() const
{
    return m_areaDesc;
}

QString CAPInfo::areaValue() const
{
    return m_areaValue;
}

AreaType CAPInfo::areaType() const
{
    return m_areaType;
}
