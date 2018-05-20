#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>

/* Enable/Disable GPS sensor.
 * Disable all the configuration option if this button is clicked.
*/

void maindialog::gps_setDefault()
{
    gpsList = {
        {MSG_START_SYM,DEVICE_ID_GPS},
        0
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
            gpsList.gps_activeHour |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            gpsList.gps_activeHour &= ~(1 << button->property("button_shift").toInt());
        }

        qDebug() << "gps time is :" << gpsList.gps_activeHour << endl;

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
                gpsList.gps_activeHour = 0;
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
            gpsList.gps_activeHour = 0;
            button->setProperty("clicked", false);
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
        }
    }
    qDebug() << "gps time is :" << gpsList.gps_activeHour << endl;
}



