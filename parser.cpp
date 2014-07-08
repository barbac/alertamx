#include <QDomDocument>
#include <QMetaEnum>
#include <QDebug>

#include "parser.h"
#include "capinfo.h"

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
        } else if (tag.toLower() == QLatin1String("info")) {
            parseInfo(child, alert->info);
        }
    }
    return true;
}

void Parser::parseInfo(const QDomElement &infoElement, CAPInfo *info) const
{
    for (QDomNode node = infoElement.firstChild();
         !node.isNull(); node = node.nextSibling()) {
        if (!node.isElement())
            continue;
        QDomElement child = node.toElement();
        QString tag = child.tagName();

        if (tag.toLower() == QLatin1String("language")) {
            info->m_language = child.text();
        } else if (tag.toLower() == QLatin1String("category")) {
            auto metaObject = CategoryGadget::staticMetaObject;
            int index = metaObject.indexOfEnumerator("Category");
            QMetaEnum categoryEnum = metaObject.enumerator(index);
            bool ok;
            int value = categoryEnum.keyToValue(child.text().toLatin1(), &ok);
            if (!ok)
                qCritical() << "Unknown Category value: " << child.text();
            info->m_category = static_cast<Category>(value);
        }
    }
}
