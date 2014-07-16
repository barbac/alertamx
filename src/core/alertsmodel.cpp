#include <QDebug>

#include "alertsmodel.h"

AlertsModel::AlertsModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int AlertsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_alerts.size();
}

QVariant AlertsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (!index.isValid() || role != AlertRole || row >= m_alerts.size())
        return QVariant();
    return QVariant::fromValue(m_alerts.at(row));
}

QHash<int, QByteArray> AlertsModel::roleNames() const
{
    return {{AlertRole, "alert"}};
}

CAPAlert *AlertsModel::appendAlert()
{
    beginInsertRows(QModelIndex(), m_alerts.size(), m_alerts.size());
    CAPAlert *alert = new CAPAlert(this);
    m_alerts.append(alert);
    endInsertRows();
    return alert;
}
