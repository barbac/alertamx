TEMPLATE = app
TARGET = alertamx
#make it a console app on osx
CONFIG -= app_bundle

include(core/alertamx.pri)
SOURCES += main.cpp

LIBS += -Lcore -lalertamx
PRE_TARGETDEPS += core/libalertamx.a
