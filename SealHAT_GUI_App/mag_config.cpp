#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

/* Enable/Disable mag sensor.
 * Disable all the configuration option if this button is clicked.
*/

void maindialog::mag_dataCollection(Mag_TX *mag)
{
    (void) mag;
    //mag->acc_activeHour = ;
}

void maindialog::on_mag_pwrBox_currentIndexChanged(int index)
{
    (void) index;
}

void maindialog::IMUmag_Disable(bool disable)
{
    ui->mag_timeclear_button->setDisabled(disable);
    ui->mag_pwrBox->setDisabled(disable);
    ui->mag_freqBox->setDisabled(disable);
    //ui->mag_finishButton->setDisabled(true);
}

void maindialog::mag_setDefault()
{
    ui->mag_pwrBox->setCurrentIndex(MAG_LP);
    ui->mag_freqBox->setCurrentIndex(MAG_FREQ_50HZ);

    configuration_settings.magnetometer_config = {
              {MSG_START_SYM, DEVICE_ID_MAGNETIC_FIELD, 0, 0, sizeof(MAG_OPMODE_t)},// header
              0,                                                                    // active hours
              MAG_LP_50_HZ                                                          // mode
              };
}

void maindialog::on_mag_SW_clicked()
{
    QString title = ui->mag_SW->text();
    if(title == "Enable")
    {
        ui->mag_SW->setText("Disable");
        IMUmag_Disable(false);
        mag_disable_button(false);
    }else{
        ui->mag_SW->setText("Enable");
        IMUmag_Disable(true);
        mag_disable_button(true);
    }
}


void maindialog::mag_timeTable_control()
{
    for(QPushButton* button : ui->magConfigPage->findChildren<QPushButton*>())
    {

        if(button->property("button_shift").isValid())
        {
            connect(button,SIGNAL(clicked()), this, SLOT(mag_hour_clicked()));
        }
    }

}

void maindialog::mag_hour_clicked()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!button->property("clicked").isValid()) {
        button->setProperty("clicked", false);
    }
    bool clicked = button->property("clicked").toBool();
    button->setProperty("clicked", !clicked);

        if(!clicked) {
            button->setStyleSheet("background-color:rgb(34,139,34)");
            configuration_settings.magnetometer_config.mag_activeHour |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            configuration_settings.magnetometer_config.mag_activeHour &= ~(1 << button->property("button_shift").toInt());
        }

        qDebug() << "mag time is :" << configuration_settings.magnetometer_config.mag_activeHour << endl;

}


void maindialog::mag_disable_button(bool disable)
{    
    for(QPushButton* button : ui->magConfigPage->findChildren<QPushButton*>()) {
        if(button->property("button_shift").isValid()) {
            button->setDisabled(disable);
            if(disable){
                configuration_settings.magnetometer_config.mag_activeHour = 0;
                button->setProperty("clicked", false);
                button->setStyleSheet("background-color:rgb(105, 105,105)");
            }else{
                button->setStyleSheet("background-color:rgb(152, 162, 173)");
            }
        }
    }
}

void maindialog::on_mag_timeclear_button_clicked()
{
    for(QPushButton* button : ui->magConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            configuration_settings.magnetometer_config.mag_activeHour = 0;
            button->setProperty("clicked", false);
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
        }
    }
    qDebug() << "mag time is :" << configuration_settings.magnetometer_config.mag_activeHour << endl;
}

