#include <QDomDocument>
#include <QMetaEnum>
#include <QDebug>

#include "parser.h"
#include "capinfo.h"

Parser::Parser()
{
}

bool Parser::parseAlert(const QString &xml, CAPAlert *alert)
{
    QDomElement element = rootElement(xml);
    if (element.tagName().toLower() != "alert") {
        qWarning() << "invalid tag name: " << element.tagName();
        return false;
    }
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
            alert->m_identifier = child.text();
        } else if (tag.toLower() == QLatin1String("sender")) {
            alert->m_sender = child.text();
        } else if (tag.toLower() == QLatin1String("sent")) {
            alert->m_sent = child.text();
        } else if (tag.toLower() == QLatin1String("code")) {
            alert->m_code = child.text();
        } else if (tag.toLower() == QLatin1String("status")) {
            alert->m_status = static_cast<Status>(child.text().toInt());
        } else if (tag.toLower() == QLatin1String("msgtype")) {
            alert->m_msgType = static_cast<MsgType>(child.text().toInt());
        } else if (tag.toLower() == QLatin1String("scope")) {
            alert->m_scope = static_cast<Scope>(child.text().toInt());
        } else if (tag.toLower() == QLatin1String("info")) {
            parseInfo(child, alert->m_info);
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
            int value = enumFromString(CategoryGadget::staticMetaObject,
                                       "Category", child.text());
            info->m_category = static_cast<Category>(value);
        } else if (tag.toLower() == QLatin1String("event")) {
            info->m_event = child.text();
        } else if (tag.toLower() == QLatin1String("responsetype")) {
            int value = enumFromString(ResponseTypeGadget::staticMetaObject,
                                       "ResponseType", child.text());
            info->m_responseType = static_cast<ResponseType>(value);
        } else if (tag.toLower() == QLatin1String("urgency")) {
            int value = enumFromString(UrgencyGadget::staticMetaObject,
                                       "Urgency", child.text());
            info->m_urgency = static_cast<Urgency>(value);
        } else if (tag.toLower() == QLatin1String("severity")) {
            int value = enumFromString(SeverityGadget::staticMetaObject,
                                       "Severity", child.text());
            info->m_severity = static_cast<Severity>(value);
        } else if (tag.toLower() == QLatin1String("certainty")) {
            int value = enumFromString(CertaintyGadget::staticMetaObject,
                                       "Certainty", child.text());
            info->m_certainty = static_cast<Certainty>(value);
        } else if (tag.toLower() == QLatin1String("effective")) {
            info->m_effective = child.text();
        } else if (tag.toLower() == QLatin1String("expires")) {
            info->m_expires = child.text();
        } else if (tag.toLower() == QLatin1String("sendername")) {
            info->m_senderName = child.text();
        } else if (tag.toLower() == QLatin1String("headline")) {
            info->m_headline = child.text();
        } else if (tag.toLower() == QLatin1String("description")) {
            info->m_description = child.text();
        } else if (tag.toLower() == QLatin1String("instruction")) {
            info->m_instruction = child.text();
        } else if (tag.toLower() == QLatin1String("web")) {
            info->m_web = child.text();
        } else if (tag.toLower() == QLatin1String("contact")) {
            info->m_contact = child.text();
        }
    }
}

QDomElement Parser::rootElement(const QString &xml) const
{
    QString errorMsg;
    int errorLine, errorColumn;
    QDomDocument document;
    bool success = document.setContent(xml, &errorMsg,
                                       &errorLine, &errorColumn);
    if (!success) {
        qWarning() << errorMsg << "Line: " << errorLine << "Column: "
                   << errorColumn << xml.split('\n').at(errorLine);
    }
    return document.documentElement();
}

int Parser::enumFromString(const QMetaObject &metaObject, const char *enumName,
                           const QString &value) const
{
    int index = metaObject.indexOfEnumerator(enumName);
    QMetaEnum categoryEnum = metaObject.enumerator(index);
    bool ok;
    int myEnum = categoryEnum.keyToValue(value.toLatin1(), &ok);
    if (!ok)
        qCritical("Unknown %s value: %s", enumName, qPrintable(value));
    return myEnum;
}
