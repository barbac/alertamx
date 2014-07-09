TEMPLATE = subdirs
SUBDIRS += src tests
#needs the static lib
tests.depends = src
