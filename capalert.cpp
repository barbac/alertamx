#include "capalert.h"
#include "capinfo.h"

CAPAlert::CAPAlert(QObject *parent) :
    QObject(parent)
{
    info = new CAPInfo(this);
}
