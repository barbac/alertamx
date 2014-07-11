#include <QtTest>
#include <QDebug>

#include "capalert.h"

class TestAlert: public QObject
{
    Q_OBJECT
private slots:
    void status();
};

void test_string_values_from_enums(const QMetaObject metaObject,
                                   std::function<QString(int)> callBack)
{
    QMetaEnum metaEnum = metaObject.enumerator(0);
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        QString result = callBack(i);
        QString error = QString("\"%1\" enum value missing string value")
                .arg(metaEnum.valueToKey(i));
        QVERIFY2(!result.isEmpty(), qPrintable(error));
    }
}

void TestAlert::status()
{
    CAPAlert alert(nullptr);
    alert.setStatus(Status::Actual);
    QCOMPARE(alert.statusString(), QStringLiteral("Actual"));
    alert.setStatus(Status::Exercise);
    QCOMPARE(alert.statusString(), QStringLiteral("Exercise"));
    alert.setStatus(Status::System);
    QCOMPARE(alert.statusString(), QStringLiteral("System"));
    alert.setStatus(Status::Test);
    QCOMPARE(alert.statusString(), QStringLiteral("Test"));
    alert.setStatus(Status::Draft);
    QCOMPARE(alert.statusString(), QStringLiteral("Draft"));

    auto callBack = [&alert](int value) -> QString {
        alert.setStatus(static_cast<Status>(value));
        return alert.statusString();
    };
    test_string_values_from_enums(StatusGadget::staticMetaObject, callBack);
}

QTEST_GUILESS_MAIN(TestAlert)
#include "tst_alert.moc"


