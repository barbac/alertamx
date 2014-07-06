#TARGET = alertamx
TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle

HEADERS += \
    parser.h

SOURCES += \
    parser.cpp \

TARGET = tst_parser
QT += testlib
CONFIG += testcase
SOURCES += \
    tst_parser.cpp
