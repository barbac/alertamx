#include <QtTest>
#include <QDebug>

#include "capinfo.h"

class TestInfo: public QObject
{
    Q_OBJECT
private slots:
    void category();
    void responseType();
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
void TestInfo::category()
{
    CAPInfo info(nullptr);
    info.setCategory(Category::Rescue);
    QCOMPARE(info.categoryString(), QStringLiteral("Rescue"));

    auto callBack = [&info](int value) -> QString {
        info.setCategory(static_cast<Category>(value));
        return info.categoryString();
    };
    test_string_values_from_enums(CategoryGadget::staticMetaObject, callBack);
}

void TestInfo::responseType()
{
    CAPInfo info(nullptr);
    info.setResponseType(ResponseType::Avoid);
    QCOMPARE(info.responseTypeString(), QStringLiteral("Avoid"));

    auto callBack = [&info](int value) -> QString {
        info.setResponseType(static_cast<ResponseType>(value));
        return info.responseTypeString();
    };
    test_string_values_from_enums(ResponseTypeGadget::staticMetaObject,
                                  callBack);
}

QTEST_GUILESS_MAIN(TestInfo)
#include "tst_info.moc"


