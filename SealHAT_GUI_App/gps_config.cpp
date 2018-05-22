#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

/* Enable/Disable GPS sensor.
 * Disable all the configuration option if this button is clicked.
*/

void maindialog::gps_dataCollect()
{
    uint8_t pwrIndex = 0;
    uint8_t freq;

    pwrIndex= ui->mag_pwrBox->currentIndex();
    freq = ui->mag_freqBox->currentIndex();

    if(pwrIndex == MAG_LP)
    {
        switch(freq){
        case MAG_FREQ_10HZ:
            configuration_settings.magnetometer_config.mag_mode = MAG_LP_10_HZ;
        break;
        case MAG_FREQ_20HZ:
            configuration_settings.magnetometer_config.mag_mode = MAG_LP_20_HZ;
        break;
        case MAG_FREQ_50HZ:
            configuration_settings.magnetometer_config.mag_mode = MAG_LP_50_HZ;
        break;
        case MAG_FREQ_100HZ:
            configuration_settings.magnetometer_config.mag_mode = MAG_LP_100_HZ;
        break;
        }

    }else if(pwrIndex == MAG_NORMAL){
            switch(freq){
            case MAG_FREQ_10HZ:
                configuration_settings.magnetometer_config.mag_mode = MAG_NORM_10_HZ;
            break;
            case MAG_FREQ_20HZ:
                configuration_settings.magnetometer_config.mag_mode = MAG_NORM_20_HZ;
            break;
            case MAG_FREQ_50HZ:
                configuration_settings.magnetometer_config.mag_mode = MAG_NORM_50_HZ;
            break;
            case MAG_FREQ_100HZ:
                configuration_settings.magnetometer_config.mag_mode = MAG_NORM_100_HZ;
            break;
            }

    }
}

void maindialog::gps_setDefault()
{
    on_gps_timeclear_button_clicked();
    configuration_settings.gps_config = {
        {MSG_START_SYM, DEVICE_ID_GPS, 0, 0, sizeof(GPS_PROFILE)},  // header
        0,                                                          // active hours
        GPS_PSMOO30S                                                // profile
    };
}

void maindialog::gps_hour_clicked()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!button->property("clicked").isValid()) {
        button->setProperty("clicked", false);
    }
    bool clicked = button->property("clicked").toBool();
    button->setProperty("clicked", !clicked);
        if(!clicked) {
            button->setStyleSheet("background-color:rgb(34,139,34)");
            configuration_settings.gps_config.gps_activeHour |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            configuration_settings.gps_config.gps_activeHour &= ~(1 << button->property("button_shift").toInt());
        }

        qDebug() << "gps time is :" << configuration_settings.gps_config.gps_activeHour << endl;

}

void maindialog::gps_timeTable_control()
{
    for(QPushButton* button : ui->gpsConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            connect(button,SIGNAL(clicked()), this, SLOT(gps_hour_clicked()));
        }
    }

}

void maindialog::gps_disable(bool disable)
{
    ui->gps_timeclear_button->setDisabled(disable);
    gps_disable_button(disable);
}

void maindialog::on_gps_SW_clicked()
{
    QString title = ui->gps_SW->text();
    if(title == "Enable")
    {
        gps_disable(false);
        ui->gps_SW->setText("Disable");
    }else{
        ui->gps_SW->setText("Enable");
        gps_disable(true);
    }
}

void maindialog::gps_disable_button(bool disable)
{
    for(QPushButton* button : ui->gpsConfigPage->findChildren<QPushButton*>()) {
        if(button->property("button_shift").isValid()) {
            button->setDisabled(disable);
            if(disable){
                configuration_settings.gps_config = {
                    {MSG_START_SYM, DEVICE_ID_GPS, 0, 0, sizeof(GPS_PROFILE)},  // header
                    0,                                                          // active hours
                    GPS_PSMOO30S                                                // profile
                };
                button->setProperty("clicked", false);
                button->setStyleSheet("background-color:rgb(105, 105,105)");
            }else{
                button->setStyleSheet("background-color:rgb(152, 162, 173)");
            }
        }
    }
}

void maindialog::on_gps_timeclear_button_clicked()
{
    for(QPushButton* button : ui->gpsConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            configuration_settings.gps_config.gps_activeHour = 0;
            button->setProperty("clicked", false);
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
        }
    }
    qDebug() << "gps time is :" << configuration_settings.gps_config.gps_activeHour << endl;
}



