#include <QtTest>
#include <QDebug>

#include "capalert.h"

class TestAlert: public QObject
{
    Q_OBJECT
private slots:
    void status();
};

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
}

QTEST_GUILESS_MAIN(TestAlert)
#include "tst_alert.moc"


