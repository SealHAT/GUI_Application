#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QTextCursor>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"
#include <QtSerialPort/QSerialPort>

/* Enable/Disable Ekg sensor.
 * Disable all the configuration option if this button is clicked.
*/


void maindialog::on_completeButton_clicked()
{

    goto_DEV();
    /*qDebug() << "ACCELEROMETER" << endl;
        qDebug() << "Final accelerometer time is :" << configuration_settings.accelerometer_config.acc_activeHour << endl;
        qDebug() << "acc_scale is 0x:" << QString::number(configuration_settings.accelerometer_config.acc_activeHour, 16) << endl;
        qDebug() << "acc_mode is 0x:" << QString::number(configuration_settings.accelerometer_config.acc_mode, 16) << endl;
        qDebug() << "acc_sensitivity is 0x:" <<QString::number(configuration_settings.accelerometer_config.acc_sensitivity, 16) << endl;
        qDebug() << "acc_threshold is 0x:" << configuration_settings.accelerometer_config.acc_threshold << endl;

    qDebug() << "MAGNETOEMTER" << endl;
        qDebug() << "mag_activeHour is :" << configuration_settings.magnetometer_config.mag_activeHour << endl;
        qDebug() << "mag_mode is 0x:" << QString::number(configuration_settings.magnetometer_config.mag_mode, 16) << endl;

    qDebug() << "EKG" << endl;
        qDebug() << "ekg_activeHour is :" << configuration_settings.ekg_config.ekg_activeHour << endl;
        qDebug() << "ekg_sampleRate is 0x:" << QString::number(configuration_settings.ekg_config.ekg_sampleRate, 16) << endl;
        qDebug() << "ekg_gain is 0x:" << QString::number(configuration_settings.ekg_config.ekg_gain, 16) << endl;
        qDebug() << "ekg_lowpassFreq is 0x:" << QString::number(configuration_settings.ekg_config.ekg_lowpassFreq, 16) << endl;

    qDebug() << "TEMPERATURE&LIGHT" << endl;
        qDebug() << "temp_activeHour is :" << configuration_settings.temperature_config.temp_activeHour << endl;
        qDebug() << "temp_samplePeriod is 0x:" << configuration_settings.temperature_config.temp_samplePeriod << endl;

    qDebug() << "GPS" << endl;
        qDebug() << "gps_activeHour is :" << configuration_settings.gps_config.gps_activeHour << endl;*/
}


void maindialog::setConfigList()
{
    QString xcel_scale = ui->xcel_scaleBox->currentText();
    //ui->xcel_ConfigList->append(xcel_scale);
}
