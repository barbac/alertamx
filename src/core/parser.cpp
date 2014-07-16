#include <QDomDocument>
#include <QMetaEnum>
#include <QDebug>

#include "parser.h"
#include "capinfo.h"

Parser::Parser()
{
}

bool Parser::parseFeed(const QString &xml, CAPAlert *alert)
{
    QDomElement root = rootElement(xml);
    if (root.isNull()) {
        return false;
    }
    QDomNodeList nodes = root.elementsByTagName(QStringLiteral("entry"));
    for (int i = 0; i < nodes.size(); ++i) {
        QDomNode node = nodes.at(i);
        if (!node.isElement()) {
            continue;
        }
        QDomElement element = node.toElement();
        auto contents = element.elementsByTagName(QStringLiteral("content"));
        if (contents.isEmpty()) {
            continue;
        }
        QDomElement firstContent = contents.at(0).toElement();
        auto entries = firstContent.elementsByTagName(QStringLiteral("alert"));
        if (entries.isEmpty()) {
            continue;
        }
        for (int j = 0; j < entries.size(); ++j) {
            QDomElement alertElement = entries.at(j).toElement();
            //TODO: Parse the rest of alerts and test them.
            return parseAlert(alertElement, alert);
        }
    }
    return true;
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
            alert->setProperty("identifier", child.text());
        } else if (tag.toLower() == QLatin1String("sender")) {
            alert->setProperty("sender", child.text());
        } else if (tag.toLower() == QLatin1String("sent")) {
            alert->setProperty("sent", child.text());
        } else if (tag.toLower() == QLatin1String("code")) {
            alert->setProperty("code", child.text());
        } else if (tag.toLower() == QLatin1String("status")) {
            alert->setStatus(static_cast<Status>(child.text().toInt()));
        } else if (tag.toLower() == QLatin1String("msgtype")) {
            alert->setMsgType(static_cast<MsgType>(child.text().toInt()));
        } else if (tag.toLower() == QLatin1String("scope")) {
            alert->setScope(static_cast<Scope>(child.text().toInt()));
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
            info->setProperty("language", child.text());
        } else if (tag.toLower() == QLatin1String("category")) {
            int value = enumFromString(CategoryGadget::staticMetaObject,
                                       "Category", child.text());
            info->setCategory(static_cast<Category>(value));
        } else if (tag.toLower() == QLatin1String("event")) {
            info->setProperty("event", child.text());
        } else if (tag.toLower() == QLatin1String("responsetype")) {
            int value = enumFromString(ResponseTypeGadget::staticMetaObject,
                                       "ResponseType", child.text());
            info->setResponseType(static_cast<ResponseType>(value));
        } else if (tag.toLower() == QLatin1String("urgency")) {
            int value = enumFromString(UrgencyGadget::staticMetaObject,
                                       "Urgency", child.text());
            info->setUrgency(static_cast<Urgency>(value));
        } else if (tag.toLower() == QLatin1String("severity")) {
            int value = enumFromString(SeverityGadget::staticMetaObject,
                                       "Severity", child.text());
            info->setSeverity(static_cast<Severity>(value));
        } else if (tag.toLower() == QLatin1String("certainty")) {
            int value = enumFromString(CertaintyGadget::staticMetaObject,
                                       "Certainty", child.text());
            info->setCertainty(static_cast<Certainty>(value));
        } else if (tag.toLower() == QLatin1String("effective")) {
            info->setProperty("effective", child.text());
        } else if (tag.toLower() == QLatin1String("expires")) {
            info->setProperty("expires", child.text());
        } else if (tag.toLower() == QLatin1String("sendername")) {
            info->setProperty("senderName", child.text());
        } else if (tag.toLower() == QLatin1String("headline")) {
            info->setProperty("headline", child.text());
        } else if (tag.toLower() == QLatin1String("description")) {
            info->setProperty("description", child.text());
        } else if (tag.toLower() == QLatin1String("instruction")) {
            info->setProperty("instruction", child.text());
        } else if (tag.toLower() == QLatin1String("web")) {
            info->setProperty("web", child.text());
        } else if (tag.toLower() == QLatin1String("contact")) {
            info->setProperty("contact", child.text());
        } else if (tag.toLower() == QLatin1String("area")) {
            parseArea(child, info);
        }
    }
}

void Parser::parseArea(const QDomElement &areaElement, CAPInfo *info) const
{
    for (QDomNode node = areaElement.firstChild();
         !node.isNull(); node = node.nextSibling()) {
        if (!node.isElement())
            continue;

        QDomElement child = node.toElement();
        QString tag = child.tagName().toLower();

        if (tag == QLatin1String("areadesc")) {
            info->setAreaDesc(child.text());
        } else if (tag == QLatin1String("polygon")) {
            info->setAreaType(AreaType::polygon);
            info->setAreaValue(child.text());
        } else if (tag == QLatin1String("circle")) {
            info->setAreaType(AreaType::circle);
            info->setAreaValue(child.text());
        } else if (tag == QLatin1String("geocode")) {
            info->setAreaType(AreaType::geocode);
            info->setAreaValue(child.text());
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
