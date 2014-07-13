#pragma once

#include "capalert.h"

class QDomElement;

class Parser
{
public:
    Parser();
    bool parseAlert(const QString &xml, CAPAlert *alert);
    bool parseAlert(const QDomElement &alertElement, CAPAlert *alert) const;
    void parseInfo(const QDomElement &infoElement, CAPInfo *info) const;

private:
    int enumFromString(const QMetaObject &metaObject, const char *enumName,
                       const QString &value) const;
};
