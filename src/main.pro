TEMPLATE = app
TARGET = alertamx
#make it a console app on osx
CONFIG -= app_bundle
QT += qml quick

include(core/alertamx.pri)
SOURCES += main.cpp
RESOURCES += qml/qml.qrc

LIBS += -Lcore -lalertamx
PRE_TARGETDEPS += core/libalertamx.a

# Default rules for deployment.
include(deployment.pri)
