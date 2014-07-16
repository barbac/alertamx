#pragma once

#include <QAbstractListModel>

#include "capalert.h"

class AlertsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        AlertRole = Qt::UserRole + 1
    };

    explicit AlertsModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    CAPAlert *appendAlert();

private:
    QList<CAPAlert *> m_alerts;

};
