#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QFile>

#include "capalert.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CAPAlert alert(nullptr);
    if (argc > 1) {
        QFile file(argv[1]);
        if (file.open(QIODevice::Text | QIODevice::ReadOnly)) {
            qDebug() << "Loading:" << argv[1];
            QString xml = file.readAll();
            Parser parser;
            if (!parser.parse(xml, &alert))
                qDebug() << "Unable parse:" << argv[1];
        } else {
            qDebug() << "Unable to open:" << argv[1] << file.errorString();
        }
    }

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
