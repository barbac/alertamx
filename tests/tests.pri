include(../src/core/alertamx.pri)
QT += testlib
CONFIG += testcase
CONFIG -= app_bundle

LIBS += -L../../src/core -lalertamx
PRE_TARGETDEPS += ../../src/core/libalertamx.a
