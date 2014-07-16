#include <QtTest>
#include <QDebug>

#include "alertsmodel.h"

class TestAlertsModel: public QObject
{
    Q_OBJECT
private slots:
    void appendAlert();
    void data();

};

void TestAlertsModel::appendAlert()
{
    AlertsModel model(nullptr);
    QSignalSpy spy(&model, SIGNAL(rowsInserted(const QModelIndex &, int, int)));
    QCOMPARE(model.rowCount(), 0);
    model.appendAlert();
    model.appendAlert();
    model.appendAlert();
    QCOMPARE(model.rowCount(), 3);
    QCOMPARE(spy.count(), 3);
}

void TestAlertsModel::data()
{
    AlertsModel model(nullptr);
    auto alert1 = model.appendAlert();
    alert1->setStatus(Status::Test);
    auto alert2 = model.appendAlert();
    alert2->setStatus(Status::System);

    QModelIndex index = model.index(0);
    QVariant data1 = model.data(index, model.AlertRole);
    CAPAlert *alertResult = data1.value<CAPAlert *>();
    QCOMPARE(alertResult->status(), Status::Test);

    index = model.index(1);
    QVariant data2 = model.data(index, model.AlertRole);
    Q_ASSERT(data2.isValid());
    CAPAlert *alertResult2 = data2.value<CAPAlert *>();
    QCOMPARE(alertResult2->status(), Status::System);
}


QTEST_GUILESS_MAIN(TestAlertsModel)
#include "tst_alertsmodel.moc"
