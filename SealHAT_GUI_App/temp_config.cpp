#include <QDesktopWidget>
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

void maindialog::on_temp_SW_clicked()
{
    QString title = ui->temp_SW->text();
    if(title == "Enable")
    {
        temp_disable(false);
        ui->temp_SW->setText("Disable");
    }else{
        ui->temp_SW->setText("Enable");
        temp_disable(true);
    }
}

void maindialog::temp_setDefault()
{
   on_temp_timeclear_button_clicked();
   ui->temp_freq->setText("1");
   configuration_settings.temperature_config = {
       {MSG_START_SYM, DEVICE_ID_LIGHT, 0, 0, sizeof(uint16_t)},// header data
       0,                                                       // active hours
       1                                                        // sample period
   };
}

void maindialog::temp_disable(bool disable)
{
    ui->temp_timeclear_button->setDisabled(disable);
    temp_disable_button(disable);
    ui->temp_freq->setDisabled(disable);
    ui->temp_warnLABEL->hide();
}

void maindialog::temp_disable_button(bool disable)
{
    for(QPushButton* button : ui->tempConfigPage->findChildren<QPushButton*>()) {
        if(button->property("button_shift").isValid()) {
            button->setDisabled(disable);
            if(disable){
                configuration_settings.temperature_config = {
                    {MSG_START_SYM, DEVICE_ID_LIGHT, 0, 0, sizeof(uint16_t)},// header data
                    0,                                                       // active hours
                    0                                                        // sample period
                };
                button->setProperty("clicked", false);
                button->setStyleSheet("background-color:rgb(105, 105,105)");
            }else{
                button->setStyleSheet("background-color:rgb(152, 162, 173)");
            }
        }
    }
}

void maindialog::temp_hour_clicked()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!button->property("clicked").isValid()) {
        button->setProperty("clicked", false);
    }
    bool clicked = button->property("clicked").toBool();
    button->setProperty("clicked", !clicked);
        if(!clicked) {
            button->setStyleSheet("background-color:rgb(34,139,34)");
            configuration_settings.temperature_config.temp_activeHour |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            configuration_settings.temperature_config.temp_activeHour &= ~(1 << button->property("button_shift").toInt());
        }
        //powerEstimation();

        //qDebug() << "temp time is :" << configuration_settings.temperature_config.temp_activeHour << endl;

}

void maindialog::temp_timeTable_control()
{
    for(QPushButton* button : ui->tempConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            connect(button,SIGNAL(clicked()), this, SLOT(temp_hour_clicked()));
        }
    }
}

void maindialog::on_temp_freq_editingFinished()
{
    int valid;
    int pos;
    QIntValidator v(1, 65000, this);

    QString thres = ui->temp_freq->text();
    valid = v.validate(thres, pos);
    if(valid != ACCEPTABLE){
        ui->temp_warnLABEL->show();

    }else{
        configuration_settings.temperature_config.temp_samplePeriod = (ui->temp_freq->text().toDouble());
        qDebug() << configuration_settings.temperature_config.temp_samplePeriod << endl;
        ui->temp_warnLABEL->hide();
    }
    //powerEstimation();
}

void maindialog::on_temp_timeclear_button_clicked()
{
    for(QPushButton* button : ui->tempConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            configuration_settings.temperature_config.temp_activeHour = 0;
            button->setProperty("clicked", false);
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
        }
    }
    //powerEstimation();
    qDebug() << "temp time is :" << configuration_settings.temperature_config.temp_activeHour << endl;
}
