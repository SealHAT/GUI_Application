#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>

/* Enable/Disable mag sensor.
 * Disable all the configuration option if this button is clicked.
*/

void maindialog::mag_dataCollection(Mag_TX *mag)
{
    //mag->acc_activeHour = ;
}

void maindialog::on_mag_pwrBox_currentIndexChanged(int index)
{

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

    magList = {
              {MSG_START_SYM,DEVICE_ID_MAGNETIC_FIELD, sizeof(MAG_OPMODE_t)},
              0,
              MAG_LP_50_HZ
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
            magList.mag_activeHour |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            magList.mag_activeHour &= ~(1 << button->property("button_shift").toInt());
        }

        qDebug() << "mag time is :" << magList.mag_activeHour << endl;

}


void maindialog::mag_disable_button(bool disable)
{    
    for(QPushButton* button : ui->magConfigPage->findChildren<QPushButton*>()) {
        if(button->property("button_shift").isValid()) {
            button->setDisabled(disable);
            if(disable){
                magList.mag_activeHour = 0;
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
            magList.mag_activeHour = 0;
            button->setProperty("clicked", false);
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
        }
    }
    qDebug() << "mag time is :" << magList.mag_activeHour << endl;
}

