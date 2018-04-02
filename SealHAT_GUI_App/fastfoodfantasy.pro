#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T10:16:42
#
#-------------------------------------------------

QT       += core gui \
         sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fastfoodfantasy
TEMPLATE = app


SOURCES += main.cpp\
    maindialog.cpp \
    configure.cpp \
    retrievedata.cpp

FORMS    += \
    maindialog.ui


HEADERS  += \
    maindialog.h

RESOURCES += \
    images.qrc
