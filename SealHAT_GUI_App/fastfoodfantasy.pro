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
    account.cpp \
    restaurant.cpp \
    fooditem.cpp \
    customer.cpp \
    customerlist.cpp \
    login.cpp \
    restaurantlist.cpp \
    travel.cpp \
    shoppingcart.cpp \
    sql.cpp

FORMS    += \
    maindialog.ui \
    shoppingcart.ui


HEADERS  += mainwindow.h \
    restaurantlist.h \
    restaurant.h \
    fooditem.h \
    maindialog.h \
    account.h \
    customer.h \
    customerlist.h \
    vertex.h \
    travel.h \
    shoppingcart.h \
    sql.h

RESOURCES += \
    images.qrc
