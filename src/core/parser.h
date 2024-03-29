#pragma once

#include "alertsmodel.h"
#include "capalert.h"

class QDomElement;

class Parser
{
public:
    Parser();
    bool parseFeed(const QString &xml, AlertsModel *model);
    bool parseAlert(const QString &xml, CAPAlert *alert);
    bool parseAlert(const QDomElement &alertElement, CAPAlert *alert) const;
    void parseInfo(const QDomElement &infoElement, CAPInfo *info) const;
    void parseArea(const QDomElement &areaElement, CAPInfo *info) const;

private:
    QDomElement rootElement(const QString &xml) const;
    int enumFromString(const QMetaObject &metaObject, const char *enumName,
                       const QString &value) const;
};
