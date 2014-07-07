#TARGET = alertamx
QT += xml
TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle

HEADERS += \
    capalert.h \
    capinfo.h \
    parser.h \

SOURCES += \
    capalert.cpp \
    capinfo.cpp \
    parser.cpp \

TARGET = tst_parser
QT += testlib
CONFIG += testcase
SOURCES += \
    tst_parser.cpp
