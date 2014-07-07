#include <QtTest>
#include <QDebug>

#include "parser.h"

class TestParser: public QObject
{
    Q_OBJECT

    Parser m_parser;
    CAPAlert *m_result = nullptr;
    QString m_xml =
u8R"(<?xml version="1.0" encoding="utf-8"?>
<alert xmlns="urn:oasis:names:tc:emergency:cap:1.2">
  <identifier>194aafab-f636-49ef-ad5e-37a1aef8d132</identifier>
  <sender>smn.cna.gob.mx</sender>
  <sent>2014-07-04T10:15:00-05:00</sent>
  <status>Actual</status>
  <msgType>Alert</msgType>
  <scope>Public</scope>
  <code>08</code>
  <info>
  </info>
</alert>
)";

private slots:
    void initTestCase();
    void alert();
};



void TestParser::initTestCase()
{
    m_result = new CAPAlert(this);
    QVERIFY(m_parser.parse(m_xml, m_result));
}

void TestParser::alert()
{
    QCOMPARE(m_result->identifier,
             QStringLiteral("194aafab-f636-49ef-ad5e-37a1aef8d132"));
    QCOMPARE(m_result->sender, QStringLiteral("smn.cna.gob.mx"));
    QCOMPARE(m_result->sent, QStringLiteral("2014-07-04T10:15:00-05:00"));
    QCOMPARE(static_cast<int>(m_result->status), static_cast<int>(Status::Actual));
    QCOMPARE(static_cast<int>(m_result->msgType), static_cast<int>(MsgType::Alert));
    QCOMPARE(static_cast<int>(m_result->scope), static_cast<int>(Scope::Public));
    QCOMPARE(m_result->code, QStringLiteral("08"));
}

QTEST_GUILESS_MAIN(TestParser)
#include "tst_parser.moc"
