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
#include <cmath>
#include "maindialog.h"
#include "ui_maindialog.h"

void maindialog::submitConfig(){
    QString acc_name = "Accelerometer";

    QString acc_timeName = "Accelerometer Time";
    uint32_t acc_timeValue = configuration_settings.accelerometer_config.acc_activeHour;
    QString acc_scaleName = "Accelerometer Scale";
    uint32_t acc_scaleValue = configuration_settings.accelerometer_config.acc_scale;
    QString acc_modeName = "Accelerometer Mode";
    uint32_t acc_modeValue = configuration_settings.accelerometer_config.acc_mode;
    QString acc_sensitivityName = "Accelerometer Sensitivity";
    uint32_t sensor_sensitivityValue = configuration_settings.accelerometer_config.acc_sensitivity;
    QString acc_thresholdName = "Accelerometer Threshold";
    uint32_t sensor_thresholdValue = configuration_settings.accelerometer_config.acc_threshold;

    QString mag_timeName = "Magnetometer Time";
    uint32_t mag_timeValue = configuration_settings.magnetometer_config.mag_activeHour;
    QString mag_mode = "Magnetometer Mode";
    uint32_t mag_modeValue = configuration_settings.magnetometer_config.mag_mode;

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
    config.insert(acc_modeName,acc_modeValue);
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
                            collectLoadingData_fromFile();
                            configureSettingListDisplay();
                    }
    }
}



/**************************************************************
 * FUNCTION: configureSettingListDisplay
 * ------------------------------------------------------------
 * This function clear the configuration list
 * on the Device Configure pages.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::configureSettingListDisplay()
{
    ui->xcel_configList->clear();

    uint8_t acc_freqSelect = (configuration_settings.accelerometer_config.acc_mode/16)%10 - 1;
    uint8_t acc_pwrSelect = (configuration_settings.accelerometer_config.acc_mode%16)/4;

    uint8_t mag_freqSelect = (configuration_settings.magnetometer_config.mag_mode%16)/4;
    uint8_t mag_pwrSelect = (configuration_settings.magnetometer_config.mag_mode/16)%10;

    QString acc_PWRMode[3]{"Normal", "High Resolution", "Low Power"};
    QString mag_PWRMode[2]{"Normal", "Low Power"};

    QString acc_timeName = "Time : ";
    QString acc_timeValue = QString::number(num_Hours(configuration_settings.accelerometer_config.acc_activeHour)) + " h ";
    QString acc_scaleName = "               Accelerometer Scale : ";
    QString acc_scaleValue = QString::number(2 << ((configuration_settings.accelerometer_config.acc_scale/16)%10)) + " g ";
    QString acc_powerMode = "\nPower Mode : " + acc_PWRMode[acc_pwrSelect];

    QString acc_freqName = "            Sampling rate : ";
    QString acc_freqValue = QString::number(accFrequency[acc_freqSelect]) + " Hz ";
    QString acc_sensitivityName = "\nSensitivity : ";
    QString sensor_sensitivityValue = QString::number(configuration_settings.accelerometer_config.acc_sensitivity);
    QString acc_thresholdName = "       Threshold : ";
    QString sensor_thresholdValue = QString::number(((double)configuration_settings.accelerometer_config.acc_threshold/1000), 'f', 2) + " g ";

    ui->xcel_configList->setText(acc_timeName + acc_timeValue +
                                acc_scaleName + acc_scaleValue +
                                acc_powerMode +
                                acc_freqName + acc_freqValue +
                                acc_sensitivityName + sensor_sensitivityValue +
                                acc_thresholdName + sensor_thresholdValue);




    QString mag_timeName = "Magnetometer Time : ";
    QString mag_timeValue = QString::number(num_Hours(configuration_settings.magnetometer_config.mag_activeHour)) + " h ";
    QString mag_powerMode = "\nPower Mode : " + mag_PWRMode[mag_pwrSelect];
    QString mag_freqName = "            Sampling rate : ";
    QString mag_freqValue = QString::number(magFrequency[mag_freqSelect])  + " Hz ";

    ui->mag_configList->setText(mag_timeName + mag_timeValue +
                                mag_powerMode +
                                mag_freqName + mag_freqValue);

    uint8_t ekg_lowpassFrequencyValue[4] = {0,40,100,150};

    QString ekg_timeName = "EKG Time : ";
    QString ekg_timeValue = QString::number(num_Hours(configuration_settings.ekg_config.ekg_activeHour))+ " h ";
    QString ekg_spsName = "                       EKG Sample Rate : ";
    QString ekg_spsValue = QString::number( (512/(pow(2,(uint8_t)configuration_settings.ekg_config.ekg_sampleRate))) ) + " samples/s ";
    QString ekg_gainName = "\nEKG Gain : ";
    QString ekg_gainValue = QString::number( 20 * (pow(2,(uint8_t)configuration_settings.ekg_config.ekg_gain) ) ) + " V ";
    QString ekg_lpfreqName = "                   EKG Low Pass Frequency : ";
    QString ekg_lpfreqValue = QString::number(ekg_lowpassFrequencyValue[configuration_settings.ekg_config.ekg_lowpassFreq]) + " Hz ";

    qDebug() << "ekg_spsValue is" << ekg_spsValue << endl;
    qDebug() << "ekg_gainValue is" << ekg_gainValue << endl;
    qDebug() << "ekg_lpfreqValue is" << ekg_lpfreqValue << endl;
    ui->ekg_configList->setText(ekg_timeName + ekg_timeValue +
                                ekg_spsName + ekg_spsValue +
                                ekg_gainName + ekg_gainValue +
                                ekg_lpfreqName + ekg_lpfreqValue
                                );


    QString templight_timeName = "Temperature & Light Time : ";
    QString templight_timeValue = QString::number(num_Hours(configuration_settings.temperature_config.temp_activeHour)) + " h ";
    QString templight_sampleperiodName = "\nTemperature and Light Sample Period : ";
    QString templight_sampleperiodValue = QString::number(configuration_settings.temperature_config.temp_samplePeriod) + " s ";
    ui->temp_configList->setText(templight_timeName + templight_timeValue +
                                templight_sampleperiodName + templight_sampleperiodValue
                                );

    QString gps_timeName = "GPS Time : ";
    QString gps_timeValue = QString::number(num_Hours(configuration_settings.gps_config.gps_activeHour)) + " h ";
    ui->gps_configList->setText(gps_timeName + gps_timeValue);
}

void maindialog::on_completeButton_clicked()
{
    goto_DEV();
    setActiveButtonColor(CONFIGURE_DEV_HOME_PAGE);
    configureSettingListDisplay();
   ui->welcomeHeadingLabel->setText("Completed configuration List");
}

