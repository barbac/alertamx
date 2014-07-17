#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QFile>
#include <QQmlContext>
#include <QtQml>

#include <QNetworkAccessManager>

#include "alertsmodel.h"
#include "parser.h"
#include "capinfo.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterUncreatableType<CAPAlert>("alertamx", 1, 0, "AlertData", "");
    qmlRegisterUncreatableType<CAPInfo>("alertamx", 1, 0, "AlertInfo", "");

    AlertsModel model(nullptr);
    engine.rootContext()->setContextProperty("alertsModel", &model);
    if (argc > 1) {
        QFile file(argv[1]);
        if (file.open(QIODevice::Text | QIODevice::ReadOnly)) {
            qDebug() << "Loading:" << argv[1];
            QString xml = file.readAll();
            Parser parser;
            if (!parser.parseFeed(xml, &model))
                qDebug() << "Unable parse:" << argv[1];
        } else {
            qDebug() << "Unable to open:" << argv[1] << file.errorString();
        }
    } else {
        QNetworkAccessManager *manager = new QNetworkAccessManager(&model);
        QUrl url = QUrl(QStringLiteral("https://correo1.conagua.gob.mx/feedsmn/feedalert.aspx"));
        QNetworkRequest request(url);
        qDebug() << "Fetching: " << url.url();
        QNetworkReply *reply = manager->get(request);
        engine.rootContext()->setContextProperty("feedProgress", reply);
        reply->setParent(manager);
        reply->connect(reply, &QNetworkReply::finished,
                       [manager, &model, reply, url]() {
            if (reply->error() != QNetworkReply::NoError) {
                qWarning() << reply->errorString();
                manager->deleteLater();
                return;
            }
            qDebug() << "Reading: " << url.url();
            QString xml = reply->readAll();
            Parser parser;
            if (!parser.parseFeed(xml, &model))
                qWarning() << "Unable to parse xml from:" << url.url();
            manager->deleteLater();
            qDebug() << "Finished fetching and parsing";
        });
    }

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
