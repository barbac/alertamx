#include <QDomDocument>
#include <QDebug>

#include "parser.h"

Parser::Parser()
{
}

bool Parser::parse(const QString &xml, CAPAlert *alert)
{
    QString errorMsg;
    int errorLine, errorColumn;
    QDomDocument document;
    bool success = document.setContent(xml, &errorMsg,
                                         &errorLine, &errorColumn);
    if (!success) {
        qWarning() << errorMsg << "Line: " << errorLine << "Column: "
                   << errorColumn << xml.split('\n').at(errorLine);
        return false;
    }
    QDomElement element = document.documentElement();
    return parseAlert(element, alert);
}

bool Parser::parseAlert(const QDomElement &alertElement, CAPAlert *alert) const
{
    for (QDomNode node = alertElement.firstChild();
         !node.isNull(); node = node.nextSibling()) {
        if (!node.isElement())
            continue;
        QDomElement child = node.toElement();
        QString tag = child.tagName();
        if (tag.toLower() == QLatin1String("identifier")) {
            alert->identifier = child.text();
        } else if (tag.toLower() == QLatin1String("sender")) {
            alert->sender = child.text();
        } else if (tag.toLower() == QLatin1String("sent")) {
            alert->sent = child.text();
        } else if (tag.toLower() == QLatin1String("code")) {
            alert->code = child.text();
        } else if (tag.toLower() == QLatin1String("status")) {
            alert->status = static_cast<Status>(child.text().toInt());
        } else if (tag.toLower() == QLatin1String("msgtype")) {
            alert->msgType = static_cast<MsgType>(child.text().toInt());
        } else if (tag.toLower() == QLatin1String("scope")) {
            alert->scope = static_cast<Scope>(child.text().toInt());
        }
    }
    return true;
}
