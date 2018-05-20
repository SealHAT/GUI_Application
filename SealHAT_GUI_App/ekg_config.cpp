#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>

/* Enable/Disable Ekg sensor.
 * Disable all the configuration option if this button is clicked.
*/

void maindialog::on_ekg_SW_clicked()
{
    QString title = ui->ekg_SW->text();
    if(title == "Enable")
    {
        ekg_Disable(false);
        ui->ekg_SW->setText("Disable");
    }else{
        ui->ekg_SW->setText("Enable");
        ekg_Disable(true);
    }
}

void maindialog::ekg_setDefault()
{
    int rmIndex1;
    int rmIndex2;
    ui->ekg_odr128->setChecked(true);
    if(ui->ekg_odr128->isChecked())
    {
        rmIndex1 = ui->ekg_LPfreqBox->findText("100 Hz");
        if(rmIndex1 >= 0)
        {
            ui->ekg_LPfreqBox->removeItem(rmIndex1);
        }
        rmIndex2 = ui->ekg_LPfreqBox->findText("150 Hz");
        if(rmIndex2 >= 0)
        {
            ui->ekg_LPfreqBox->removeItem(rmIndex2);
        }
    }
    ui->ekg_gainBox->setCurrentIndex(EKG_20_GAIN);
    ui->ekg_LPfreqBox->setCurrentIndex(EKG_LP_FREQ_40HZ);

    ekgList = {
        {MSG_START_SYM,DEVICE_ID_EKG},
        0,
        RATE_MIN_SPS,
        GAIN_20_V,
        DLPF_40_HZ
    };
}


void maindialog::ekg_hour_clicked()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!button->property("clicked").isValid()) {
        button->setProperty("clicked", false);
    }
    bool clicked = button->property("clicked").toBool();
    button->setProperty("clicked", !clicked);
        if(!clicked) {
            button->setStyleSheet("background-color:rgb(34,139,34)");
            ekgList.ekg_activeHour |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            ekgList.ekg_activeHour &= ~(1 << button->property("button_shift").toInt());
        }

        qDebug() << "ekg time is :" << ekgList.ekg_activeHour << endl;

}

void maindialog::ekg_timeTable_control()
{
    for(QPushButton* button : ui->ekgConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            connect(button,SIGNAL(clicked()), this, SLOT(ekg_hour_clicked()));
        }
    }
}

void maindialog::ekg_Disable(bool disable)
{
    ui->ekg_odr128->setDisabled(disable);
    ui->ekg_odr256->setDisabled(disable);
    ui->ekg_odr512->setDisabled(disable);
    ui->ekg_gainBox->setDisabled(disable);
    ui->ekg_LPfreqBox->setDisabled(disable);
    ekg_disable_button(disable);
}


void maindialog::on_ekg_odr128_clicked()
{
    int rmIndex1;
    int rmIndex2;
    if(ui->ekg_odr128->isChecked())
    {
        rmIndex1 = ui->ekg_LPfreqBox->findText("100 Hz");
        if(rmIndex1 >= 0)
        {
            ui->ekg_LPfreqBox->removeItem(rmIndex1);
        }
        rmIndex2 = ui->ekg_LPfreqBox->findText("150 Hz");
        if(rmIndex2 >= 0)
        {
            ui->ekg_LPfreqBox->removeItem(rmIndex2);
        }
    }
}

void maindialog::on_ekg_odr256_clicked()
{
    int addIndex;
    int rmIndex2;
    if(ui->ekg_odr256->isChecked())
    {
        addIndex = ui->ekg_LPfreqBox->findText("100 Hz");
        if(addIndex < 0)
        {
            ui->ekg_LPfreqBox->insertItem(EKG_LP_FREQ_100HZ,"100 Hz");
        }
        rmIndex2 = ui->ekg_LPfreqBox->findText("150 Hz");
        if(rmIndex2 >= 0)
        {
            ui->ekg_LPfreqBox->removeItem(rmIndex2);
        }
    }
}

void maindialog::on_ekg_odr512_clicked()
{
    int addIndex1;
    int addIndex2;
    if(ui->ekg_odr512->isChecked())
    {
        addIndex1 = ui->ekg_LPfreqBox->findText("100 Hz");
        addIndex2 = ui->ekg_LPfreqBox->findText("150 Hz");
        if(addIndex1 < 0)
        {
            ui->ekg_LPfreqBox->addItem("100 Hz");
        }
        if(addIndex2 < 0)
        {
            ui->ekg_LPfreqBox->addItem("150 Hz");
        }
    }
}

void maindialog::ekg_disable_button(bool disable)
{
    for(QPushButton* button : ui->ekgConfigPage->findChildren<QPushButton*>()) {
        if(button->property("button_shift").isValid())
        {
            button->setDisabled(disable);
            if(disable){
                ekgList.ekg_activeHour = 0;
                button->setProperty("clicked", false);
                button->setStyleSheet("background-color:rgb(105, 105,105)");
            }else{
                button->setStyleSheet("background-color:rgb(152, 162, 173)");
            }
        }
    }
}


void maindialog::on_ekg_timeclear_button_clicked()
{
    for(QPushButton* button : ui->ekgConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            ekgList.ekg_activeHour = 0;
            button->setProperty("clicked", false);
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
        }
    }
    qDebug() << "ekg time is :" << ekgList.ekg_activeHour << endl;
}

