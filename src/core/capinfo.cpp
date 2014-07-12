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
