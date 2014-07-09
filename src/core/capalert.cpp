#include "capalert.h"
#include "capinfo.h"

CAPAlert::CAPAlert(QObject *parent) :
    QObject(parent)
{
    m_info = new CAPInfo(this);
}
