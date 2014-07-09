#include <QtTest>
#include <QDebug>

#include "parser.h"
#include "capinfo.h"

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
    <language>es-419</language>
    <category>Met</category>
    <event>Aviso de Ciclón Tropical en el Atlántico</event>
    <responseType>Execute</responseType>
    <urgency>Immediate</urgency>
    <severity>Unknown</severity>
    <certainty>Observed</certainty>
    <effective>2014-07-04T10:15:00-05:00</effective>
    <expires>2014-07-04T22:15:00-05:00</expires>
    <senderName>Comisión Nacional del Agua - Servicio Meteorológico Nacional</senderName>
    <headline>HURACÁN “ARTHUR” AHORA CON CATEGORIA I</headline>
    <description>El huracán “Arthur”, se encuentra al oriente del Estado de Maryland, EUA. Por su lejanía y trayectoria no representa riesgo para México</description>
    <instruction>ninguno</instruction>
    <web>http://smn.cna.gob.mx/</web>
    <contact>webmaster@conagua.gob.mx</contact>
    <parameter>
      <valueName>Elaboró</valueName>
      <value>MÓNICA JIMÉNEZ</value>
    </parameter>
    <parameter>
      <valueName>Revisó</valueName>
      <value>EDUARDO SÁNCHEZ</value>
    </parameter>
    <parameter>
      <valueName>layer:Google:Region:0.1</valueName>
      <value>Quintana Roo y Quintana Roo</value>
    </parameter>
    <parameter>
      <valueName>categoría</valueName>
      <value>Huracán categoría III</value>
    </parameter>
    <parameter>
      <valueName>distancia</valueName>
      <value>morethan500km</value>
    </parameter>
    <area>
      <areaDesc>2217 KM al nor-noreste de Cabo Catoche, Q. Roo 2241 KM al nor-noreste de Cancún, Q. Roo 2280 KM al nor-noreste de Río Lagartos, Yuc. 2366 KM al nor-noreste de Tulum, Q. Roo 2342 KM al nor-noreste de Dzilam, Yuc.</areaDesc>
      <circle>13.752724664397,-108.2373046875 2502.6978654433624</circle>
    </area>
  </info>
</alert>
)";

private slots:
    void initTestCase();
    void alert();
    void parseInfo();
};



void TestParser::initTestCase()
{
    m_result = new CAPAlert(this);
    QVERIFY(m_parser.parse(m_xml, m_result));
}

void TestParser::alert()
{
    QCOMPARE(m_result->m_identifier,
             QStringLiteral("194aafab-f636-49ef-ad5e-37a1aef8d132"));
    QCOMPARE(m_result->m_sender, QStringLiteral("smn.cna.gob.mx"));
    QCOMPARE(m_result->m_sent, QStringLiteral("2014-07-04T10:15:00-05:00"));
    QCOMPARE(static_cast<int>(m_result->m_status), static_cast<int>(Status::Actual));
    QCOMPARE(static_cast<int>(m_result->m_msgType), static_cast<int>(MsgType::Alert));
    QCOMPARE(static_cast<int>(m_result->m_scope), static_cast<int>(Scope::Public));
    QCOMPARE(m_result->m_code, QStringLiteral("08"));
}

void TestParser::parseInfo()
{
    CAPInfo *info = m_result->m_info;
    QCOMPARE(info->m_language, QStringLiteral("es-419"));

    QCOMPARE(static_cast<int>(info->m_category),
             static_cast<int>(Category::Met));
    QCOMPARE(info->m_event,
             QStringLiteral("Aviso de Ciclón Tropical en el Atlántico"));
    //TODO: find out what exactly does this means:
    //(2)   Multiple instances MAY occur within an <info> block.
    QCOMPARE(static_cast<int>(info->m_responseType),
             static_cast<int>(ResponseType::Execute));
    QCOMPARE(static_cast<int>(info->m_urgency),
             static_cast<int>(Urgency::Immediate));
    QCOMPARE(static_cast<int>(info->m_severity),
             static_cast<int>(Severity::Unknown));
    //(3) For backward compatibility with CAP 1.0, the deprecated value of
    //“Very Likely” SHOULD be treated as equivalent to “Likely”.
    QCOMPARE(static_cast<int>(info->m_certainty),
             static_cast<int>(Certainty::Observed));
    //QString m_audience;
    //eventCode
    QCOMPARE(info->m_effective, QStringLiteral("2014-07-04T10:15:00-05:00"));
    //QString m_onset;
    QCOMPARE(info->m_expires, QStringLiteral("2014-07-04T22:15:00-05:00"));
    QCOMPARE(info->m_senderName, QStringLiteral("Comisión Nacional del Agua - Servicio Meteorológico Nacional"));
    QCOMPARE(info->m_headline, QStringLiteral("HURACÁN “ARTHUR” AHORA CON CATEGORIA I"));
    QCOMPARE(info->m_description, QStringLiteral("El huracán “Arthur”, se encuentra al oriente del Estado de Maryland, EUA. Por su lejanía y trayectoria no representa riesgo para México"));
    QCOMPARE(info->m_instruction, QStringLiteral("ninguno"));
    QCOMPARE(info->m_web, QStringLiteral("http://smn.cna.gob.mx/"));
    QCOMPARE(info->m_contact, QStringLiteral("webmaster@conagua.gob.mx"));
}

QTEST_GUILESS_MAIN(TestParser)
#include "tst_parser.moc"