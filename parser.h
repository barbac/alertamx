#ifndef PARSER_H
#define PARSER_H

#include "capalert.h"

class QDomElement;

class Parser
{
public:
    Parser();
    bool parse(const QString &xml, CAPAlert *alert);
    bool parseAlert(const QDomElement &alertElement, CAPAlert *alert) const;
    void parseInfo(const QDomElement &infoElement, CAPInfo *info) const;

private:
};

#endif
