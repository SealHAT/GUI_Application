#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T10:16:42
#
#-------------------------------------------------

QT       += core gui serialport
         sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fastfoodfantasy
TEMPLATE = app


SOURCES += main.cpp\
    maindialog.cpp \
    retrievedata.cpp \
    loading_data.cpp \
    analyze.cpp \
    config_pages/config_list.cpp \
    config_pages/configure.cpp \
    config_pages/ekg_config.cpp \
    config_pages/gps_config.cpp \
    config_pages/mag_config.cpp \
    config_pages/temp_config.cpp \
    config_pages/xcel_config.cpp \
    receiving_serialization.cpp \
    sending_serialization.cpp

FORMS    += \
    maindialog.ui


HEADERS  += \
    maindialog.h \
    sensor_header/LSM303AGR.h \
    sensor_header/LSM303AGRTypes.h \
    sensor_header/max44009Types.h \
    sensor_header/si705xTypes.h \
    sensor_header/gps.h \
    sensor_header/max30003types.h \
    sensor_header/ubx/ubxaid.h \
    sensor_header/ubx/ubxcfg.h \
    sensor_header/ubx/ubxlog.h \
    sensor_header/ubx/ubxmon.h \
    sensor_header/ubx/ubxnav.h \
    sensor_header/ubx/ubxrxm.h \
    sensor_header/ubx/ubxutils.h \
    sensor_header/ubx/ubx.h \
    sensor_header/ubx/ubxmessage.h \
    seal_Types.h \
    analyze.h \
    debug/moc_predefs.h \
    sensor_header/ubx/ubx.h \
    sensor_header/ubx/ubxaid.h \
    sensor_header/ubx/ubxcfg.h \
    sensor_header/ubx/ubxlog.h \
    sensor_header/ubx/ubxmessage.h \
    sensor_header/ubx/ubxmon.h \
    sensor_header/ubx/ubxnav.h \
    sensor_header/ubx/ubxrxm.h \
    sensor_header/ubx/ubxutils.h \
    sensor_header/gps.h \
    sensor_header/LSM303AGR.h \
    sensor_header/LSM303AGRTypes.h \
    sensor_header/max30003types.h \
    sensor_header/max44009.h \
    sensor_header/max44009Types.h \
    sensor_header/si705x.h \
    sensor_header/si705xTypes.h \
    sensor_header/ubx.h \
    analyze.h \
    maindialog.h \
    seal_Types.h \
    ui_login.h \
    ui_maindialog.h

RESOURCES += \
    images.qrc
