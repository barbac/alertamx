TEMPLATE = subdirs
SUBDIRS += core main.pro
#needs the static lib
main.pro.depends = core
CONFIG += ordered
