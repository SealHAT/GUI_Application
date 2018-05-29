#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <QtWidgets>
#include <QByteArray>
#include "maindialog.h"
#include "ui_maindialog.h"
/*
QByteArray maindialog::config_serialize(){
    QByteArray byteArray;

    QDataStream stream(&byteArray, QSerialPort::WriteOnly); //QIODevice:WriteOnly
    stream.setVersion(QDataStream::Qt_4_5);

    stream << configuration_settings.config_header.startSym
           << configuration_settings.config_header.id
           << (quint32)configuration_settings.config_header.timestamp
           << (quint16)configuration_settings.config_header.msTime
           << (quint16)configuration_settings.config_header.size

           << (quint8)configuration_settings.num_flash_chips

           << configuration_settings.start_logging_day.day
           << configuration_settings.start_logging_day.month
           << configuration_settings.start_logging_day.year

           << configuration_settings.start_logging_time

           << configuration_settings.accelerometer_config.acc_headerData.id
           << configuration_settings.config_header.timestamp
           << configuration_settings.config_header.msTime
           << configuration_settings.config_header.size;

    return byteArray;

}*/
