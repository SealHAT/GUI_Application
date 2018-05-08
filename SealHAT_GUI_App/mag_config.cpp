#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>

/* Enable/Disable mag sensor.
 * Disable all the configuration option if this button is clicked.
*/

void maindialog::IMUmag_Disable()
{
    ui->mag_pwrBox->setDisabled(true);
    ui->mag_freqBox->setDisabled(true);
    //ui->mag_finishButton->setDisabled(true);
}

void maindialog::IMUmag_Enable()
{
    ui->mag_pwrBox->setDisabled(false);
    ui->mag_freqBox->setDisabled(false);
    //ui->mag_finishButton->setDisabled(false);

}

void maindialog::on_mag_SW_clicked()
{
    QString title = ui->mag_SW->text();
    if(title == "Enable")
    {
        ui->mag_SW->setText("Disable");
        IMUmag_Enable();
        mag_disable_button(false);
    }else{
        ui->mag_SW->setText("Enable");
        IMUmag_Disable();
        mag_disable_button(true);
    }
}


void maindialog::mag_timeTable_control()
{
    for(QPushButton* button : ui->magConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            connect(button,SIGNAL(clicked()), this, SLOT(hour_clicked()));
        }
    }

}


void maindialog::mag_disable_button(bool disable)
{

    for(QPushButton* button : ui->magConfigPage->findChildren<QPushButton*>()) {
        if(button->property("button_shift").isValid()) {
            button->setDisabled(disable);
            if(disable){
                button->setProperty("clicked", false);
                button->setStyleSheet("background-color:rgb(105, 105,105)");
            }else{
                button->setStyleSheet("background-color:rgb(152, 162, 173)");
            }
        }
    }
}

