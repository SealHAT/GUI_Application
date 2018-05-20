#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QIntValidator>

#include <QDebug>

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
   ui->temp_freq->setText("1");

   tempList = {
       {MSG_START_SYM, DEVICE_ID_LIGHT},
       0,
       1
   };
}

void maindialog::temp_disable(bool disable)
{
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
                tempList.temp_activeHour = 0;
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
            tempList.temp_activeHour |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            tempList.temp_activeHour &= ~(1 << button->property("button_shift").toInt());
        }

        qDebug() << "temp time is :" << tempList.temp_activeHour << endl;

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
    //qDebug() << valid;
    if(valid != ACCEPTABLE){
        ui->temp_warnLABEL->show();

    }else{
        ui->temp_warnLABEL->hide();
    }
}

void maindialog::on_temp_timeclear_button_clicked()
{
    for(QPushButton* button : ui->tempConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            tempList.temp_activeHour = 0;
            button->setProperty("clicked", false);
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
        }
    }
    qDebug() << "temp time is :" << tempList.temp_activeHour << endl;
}
