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
    retrievedata.cpp \
    temp_config.cpp \
    ekg_config.cpp \
    gps_config.cpp \
    mag_config.cpp \
    xcel_config.cpp \
    config_list.cpp

FORMS    += \
    maindialog.ui


HEADERS  += \
    maindialog.h \
    LSM303AGRTypes.h \
    LSM303AGR.h \
    sensor_header/LSM303AGR.h \
    sensor_header/LSM303AGRTypes.h \
    sensor_header/max44009.h \
    sensor_header/max44009Types.h \
    sensor_header/seal_Types.h \
    sensor_header/si705x.h \
    sensor_header/si705xTypes.h \
    sensor_header/gps.h \
    sensor_header/max30003types.h \
    sensor_header/ubxmessage.h

RESOURCES += \
    images.qrc
