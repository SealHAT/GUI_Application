#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QList>
#include <QMessageBox>
#include <QDataStream>
#include "maindialog.h"
#include "ui_maindialog.h"


void maindialog::on_backButton_retrieveData_clicked()
{
    on_backButton_clicked();
}

void maindialog::on_storeData_destinationEdit_returnPressed()
{
    QString path = ui->storeData_destinationEdit->text();
     QDir newDir;
     if(!newDir.exists(path)){
         QMessageBox::information(this,tr("created new directory"), path);
         newDir.mkpath(path);
         qDebug()<<"Created new directory";
     }
}

void maindialog::on_chooseDestButton_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory"),
                "C:/Users/hpan5/Downloads/gui",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
            );

    ui->storeData_destinationEdit->setText(dir);
}

void maindialog::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Open saved configuration setting"),
                                                    "C:/Users/hpan5/Downloads/gui",
                                                    tr("Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"));
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

            QTextStream out(&file);
             QString sensor_name = "Accelerometer";
             QString sensor_time = QString::number(configuration_settings.accelerometer_config.acc_activeHour, 16);


            out << sensor_name << endl;
                out << "Final accelerometer time is :" << configuration_settings.accelerometer_config.acc_activeHour << endl;
                out << "acc_scale is 0x:" << QString::number(configuration_settings.accelerometer_config.acc_activeHour, 16) << endl;
                out << "acc_mode is 0x:" << QString::number(configuration_settings.accelerometer_config.acc_mode, 16) << endl;
                out << "acc_sensitivity is 0x:" <<QString::number(configuration_settings.accelerometer_config.acc_sensitivity, 16) << endl;
                out << "acc_threshold is 0x:" << configuration_settings.accelerometer_config.acc_threshold << endl;

            out << "MAGNETOEMTER" << endl;
                out << "mag_activeHour is :" << configuration_settings.magnetometer_config.mag_activeHour << endl;
                out << "mag_mode is 0x:" << QString::number(configuration_settings.magnetometer_config.mag_mode, 16) << endl;

            out << "EKG" << endl;
                out << "ekg_activeHour is :" << configuration_settings.ekg_config.ekg_activeHour << endl;
                out << "ekg_sampleRate is 0x:" << QString::number(configuration_settings.ekg_config.ekg_sampleRate, 16) << endl;
                out << "ekg_gain is 0x:" << QString::number(configuration_settings.ekg_config.ekg_gain, 16) << endl;
                out << "ekg_lowpassFreq is 0x:" << QString::number(configuration_settings.ekg_config.ekg_lowpassFreq, 16) << endl;

            out << "TEMPERATURE&LIGHT" << endl;
                out << "temp_activeHour is :" << configuration_settings.temperature_config.temp_activeHour << endl;
                out << "temp_samplePeriod is 0x:" << configuration_settings.temperature_config.temp_samplePeriod << endl;

            out << "GPS" << endl;
                out << "gps_activeHour is :" << configuration_settings.gps_config.gps_activeHour << endl;
                }
}




void maindialog::on_getDataButton_clicked()
{
    QString path = ui->storeData_destinationEdit->text();
    QDir dir;


    if(!dir.exists(path)){
        dir.mkpath(path);
        QMessageBox::information(this,tr("created new directory"), path);
    }

    QFile file( path +"/config.out.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
           return;
    qDebug()<<"file now exists";

       QTextStream out(&file);

       out << "ACCELEROMETER" << endl;
           out << "Final accelerometer time is :" << configuration_settings.accelerometer_config.acc_activeHour << endl;
           out << "acc_scale is 0x:" << QString::number(configuration_settings.accelerometer_config.acc_activeHour, 16) << endl;
           out << "acc_mode is 0x:" << QString::number(configuration_settings.accelerometer_config.acc_mode, 16) << endl;
           out << "acc_sensitivity is 0x:" <<QString::number(configuration_settings.accelerometer_config.acc_sensitivity, 16) << endl;
           out << "acc_threshold is 0x:" << configuration_settings.accelerometer_config.acc_threshold << endl;

       out << "MAGNETOEMTER" << endl;
           out << "mag_activeHour is :" << configuration_settings.magnetometer_config.mag_activeHour << endl;
           out << "mag_mode is 0x:" << QString::number(configuration_settings.magnetometer_config.mag_mode, 16) << endl;

       out << "EKG" << endl;
           out << "ekg_activeHour is :" << configuration_settings.ekg_config.ekg_activeHour << endl;
           out << "ekg_sampleRate is 0x:" << QString::number(configuration_settings.ekg_config.ekg_sampleRate, 16) << endl;
           out << "ekg_gain is 0x:" << QString::number(configuration_settings.ekg_config.ekg_gain, 16) << endl;
           out << "ekg_lowpassFreq is 0x:" << QString::number(configuration_settings.ekg_config.ekg_lowpassFreq, 16) << endl;

       out << "TEMPERATURE&LIGHT" << endl;
           out << "temp_activeHour is :" << configuration_settings.temperature_config.temp_activeHour << endl;
           out << "temp_samplePeriod is 0x:" << configuration_settings.temperature_config.temp_samplePeriod << endl;

       out << "GPS" << endl;
           out << "gps_activeHour is :" << configuration_settings.gps_config.gps_activeHour << endl;


}

