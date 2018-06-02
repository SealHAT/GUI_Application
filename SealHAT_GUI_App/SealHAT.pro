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
    configure.cpp \
    temp_config.cpp \
    ekg_config.cpp \
    gps_config.cpp \
    mag_config.cpp \
    xcel_config.cpp \
    config_list.cpp \
    analyze.cpp \
    loading_data.cpp \
    sending_serialization.cpp \
    receiving_serialization.cpp \
    data_retrieval.cpp

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
    analyze.h \
    seal_Types.h \
    retrieval_headers/seal_CTRL.h \
    retrieval_headers/seal_DATA.h \
    retrieval_headers/seal_ENV.h \
    retrieval_headers/seal_GPS.h \
    retrieval_headers/seal_IMU.h \
    retrieval_headers/seal_SERIAL.h

RESOURCES += \
    images.qrc
