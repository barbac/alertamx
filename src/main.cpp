#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QFile>
#include <QQmlContext>
#include <QtQml>

#include <QNetworkAccessManager>

#include "capalert.h"
#include "capinfo.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterUncreatableType<CAPAlert>("alertamx", 1, 0, "AlertData", "");

    CAPAlert alert(nullptr);
    engine.rootContext()->setContextProperty("alertData", &alert);
    engine.rootContext()->setContextProperty("infoData", alert.m_info);
    if (argc > 1) {
        QFile file(argv[1]);
        if (file.open(QIODevice::Text | QIODevice::ReadOnly)) {
            qDebug() << "Loading:" << argv[1];
            QString xml = file.readAll();
            Parser parser;
            if (!parser.parseFeed(xml, &alert))
                qDebug() << "Unable parse:" << argv[1];
        } else {
            qDebug() << "Unable to open:" << argv[1] << file.errorString();
        }
    } else {
        QNetworkAccessManager *manager = new QNetworkAccessManager(&alert);
        QUrl url = QUrl(QStringLiteral("https://correo1.conagua.gob.mx/feedsmn/feedalert.aspx"));
        QNetworkRequest request(url);
        qDebug() << "Fetching: " << url.url();
        QNetworkReply *reply = manager->get(request);
        reply->setParent(manager);
        reply->connect(reply, &QNetworkReply::finished,
                       [manager, &alert, reply, url]() {
            if (reply->error() != QNetworkReply::NoError) {
                qWarning() << reply->errorString();
                manager->deleteLater();
                return;
            }
            qDebug() << "Reading: " << url.url();
            QString xml = reply->readAll();
            Parser parser;
            if (!parser.parseFeed(xml, &alert))
                qWarning() << "Unable to parse xml from:" << url.url();
            manager->deleteLater();
            qDebug() << "Finished fetching and parsing";
        });
    }

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
