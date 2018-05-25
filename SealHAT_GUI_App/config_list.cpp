#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QList>
#include <QMap>
#include <QMessageBox>
#include <QDataStream>
#include "maindialog.h"
#include "ui_maindialog.h"

void maindialog::submitConfig(){
    QString acc_name = "Accelerometer";

    QString acc_timeName = "Accelerometer Time";
    uint32_t acc_timeValue = configuration_settings.accelerometer_config.acc_activeHour;
    QString acc_scaleName = "Accelerometer Scale";
    uint32_t acc_scaleValue = configuration_settings.accelerometer_config.acc_scale;
    QString acc_sensitivityName = "Accelerometer Sensitivity";
    uint32_t sensor_sensitivityValue = configuration_settings.accelerometer_config.acc_sensitivity;
    QString acc_thresholdName = "Accelerometer Threshold";
    uint32_t sensor_thresholdValue = configuration_settings.accelerometer_config.acc_threshold;

    QString mag_timeName = "Magnetometer Time";
    uint32_t mag_timeValue = configuration_settings.accelerometer_config.acc_activeHour;
    QString mag_mode = "Magnetometer Mode";
    uint32_t mag_modeValue = configuration_settings.accelerometer_config.acc_scale;

    QString ekg_timeName = "EKG Time";
    uint32_t ekg_timeValue = configuration_settings.ekg_config.ekg_activeHour;
    QString ekg_spsName = "EKG Sample Rate";
    uint32_t ekg_spsValue = configuration_settings.ekg_config.ekg_sampleRate;
    QString ekg_gainName = "EKG Gain";
    uint32_t ekg_gainValue = configuration_settings.ekg_config.ekg_gain;
    QString ekg_lpfreqName = "EKG Low Pass Frequency";
    uint32_t ekg_lpfreqValue = configuration_settings.ekg_config.ekg_lowpassFreq;

    QString templight_timeName = "Temperature and Light Time";
    uint32_t templight_timeValue = configuration_settings.temperature_config.temp_activeHour;
    QString templight_sampleperiodName = "Temperature and Light Sample Period";
    uint32_t templight_sampleperiodValue = configuration_settings.temperature_config.temp_samplePeriod;

    QString gps_timeName = "GPS Time";
    uint32_t gps_timeValue = configuration_settings.gps_config.gps_activeHour;

    config.insert(acc_timeName,acc_timeValue);
    config.insert(acc_scaleName,acc_scaleValue);
    config.insert(acc_sensitivityName,sensor_sensitivityValue);
    config.insert(acc_thresholdName,sensor_thresholdValue);

    config.insert(mag_timeName,mag_timeValue);
    config.insert(mag_mode,mag_modeValue);

    config.insert(ekg_timeName,ekg_timeValue);
    config.insert(ekg_spsName,ekg_spsValue);
    config.insert(ekg_gainName,ekg_gainValue);
    config.insert(ekg_lpfreqName,ekg_lpfreqValue);

    config.insert(templight_timeName,templight_timeValue);
    config.insert(templight_sampleperiodName,templight_sampleperiodValue);

    config.insert(ekg_gainName,ekg_gainValue);
    config.insert(ekg_lpfreqName,ekg_lpfreqValue);

    config.insert(gps_timeName,gps_timeValue);

    QMapIterator<QString, uint32_t> iter(config);

        while(iter.hasNext())
        {
            iter.next();
            qDebug() << iter.key() << " : " << iter.value();
        }


}

void maindialog::on_saveButton_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Destination Address"),
                                                    "C:/Users/hpan5/Downloads/gui",
                                                    tr("Text files (*.txt);;XML files (*.xml)"));
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly| QIODevice::Text)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

            submitConfig();

            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_4_5);
            out << config;
            file.close();
            qDebug() <<"File size is:"<< file.size() << "now";
                }

    QMapIterator<QString, uint32_t> iter(config);

        while(iter.hasNext())
        {
            iter.next();
            qDebug() << iter.key() << " : " << iter.value();
        }

}

void maindialog::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open saved configuration setting"),
                                                    "C:/Users/hpan5/Downloads/gui",
                                                    tr("Text files (*.txt);;XML files (*.xml)"));
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_4_5);
            config.clear();   // clear existing contacts
            in >> config;
            if (config.isEmpty()) {
                        QMessageBox::information(this, tr("No contacts in file"),
                            tr("The file you are attempting to open contains no settings."));
                    } else {
                        QMap<QString, uint32_t>::iterator i = config.begin();

                        while (i != config.constEnd()) {
                            qDebug() << i.key() << ": " << i.value() << endl;
                            ++i;
                        }
                    }
    }
}

void maindialog::collectLoadingData_fromFile()
{
    configuration_settings.accelerometer_config.acc_activeHour = config[ "Accelerometer Time"];
    configuration_settings.accelerometer_config.acc_scale = (ACC_FULL_SCALE_t)config[ "Accelerometer Scale"];
    configuration_settings.accelerometer_config.acc_sensitivity = config[ "Accelerometer Sensitivity"];
    configuration_settings.accelerometer_config.acc_threshold = config["Accelerometer Threshold"];


}

void maindialog::configureSettingListDisplay()
{

}

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
