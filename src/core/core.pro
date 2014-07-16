include(alertamx.pri)

TEMPLATE = lib
CONFIG += staticlib
TARGET = alertamx

HEADERS += \
    $$PWD/capalert.h \
    $$PWD/capinfo.h \
    $$PWD/parser.h \
    $$PWD/alertsmodel.h \

SOURCES += \
    $$PWD/capalert.cpp \
    $$PWD/capinfo.cpp \
    $$PWD/parser.cpp \
    $$PWD/alertsmodel.cpp \
