#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

/* Enable/Disable Ekg sensor.
 * Disable all the configuration option if this button is clicked.
*/

void maindialog::on_ekg_gainBox_currentIndexChanged(int index)
{
    switch(index){
    case EKG_20_GAIN:
        configuration_settings.ekg_config.ekg_gain = GAIN_20_V;
        break;
    case EKG_40_GAIN:
        configuration_settings.ekg_config.ekg_gain = GAIN_40_V;
        break;
    case EKG_80_GAIN:
        configuration_settings.ekg_config.ekg_gain = GAIN_80_V;
        break;
    case EKG_160_GAIN:
        configuration_settings.ekg_config.ekg_gain = GAIN_160_V;
        break;
    }
    qDebug() << "ekg gain is 0x:" << QString::number(configuration_settings.ekg_config.ekg_gain, 16) << endl;

}


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
    uint16_t size;
    ui->ekg_odr128->setChecked(true);
    on_ekg_odr128_clicked();

    ui->ekg_gainBox->setCurrentIndex(EKG_20_GAIN);
    ui->ekg_LPfreqBox->setCurrentIndex(EKG_LP_FREQ_40HZ);
    on_ekg_timeclear_button_clicked();

    size = sizeof(CNFGECG_RATE_VAL) + sizeof(CNFGECG_GAIN_VAL) + sizeof(CNFGECG_DLPF_VAL);
    configuration_settings.ekg_config = {
        {MSG_START_SYM,DEVICE_ID_EKG, 0, 0, size},  // header
        0,                                          // active hours
        RATE_MIN_SPS,                               // sampling rate
        GAIN_20_V,                                  // gain
        DLPF_40_HZ                                  // frequency
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
            configuration_settings.ekg_config.ekg_activeHour |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            configuration_settings.ekg_config.ekg_activeHour &= ~(1 << button->property("button_shift").toInt());
        }

        qDebug() << "ekg time is :" << configuration_settings.ekg_config.ekg_activeHour << endl;

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

void maindialog::ekg_powerEstimation_control()
{
    for(QRadioButton* button : ui->ekgConfigPage->findChildren<QRadioButton*>())
    {
            connect(button,SIGNAL(clicked()), this, SLOT(powerEstimation()));

    }
}

void maindialog::ekg_Disable(bool disable)
{
    ui->ekg_timeclear_button->setDisabled(disable);
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
        configuration_settings.ekg_config.ekg_sampleRate = RATE_MIN_SPS;
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
        configuration_settings.ekg_config.ekg_sampleRate = RATE_MED_SPS;
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
        configuration_settings.ekg_config.ekg_sampleRate = RATE_MAX_SPS;
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
    //qDebug() << "ekg sps is :" << configuration_settings.ekg_config.ekg_sampleRate << endl;

}

void maindialog::ekg_disable_button(bool disable)
{
    uint16_t size;
    for(QPushButton* button : ui->ekgConfigPage->findChildren<QPushButton*>()) {
        if(button->property("button_shift").isValid())
        {
            button->setDisabled(disable);
            if(disable){
                size = sizeof(CNFGECG_RATE_VAL) + sizeof(CNFGECG_GAIN_VAL) + sizeof(CNFGECG_DLPF_VAL);
                configuration_settings.ekg_config = {
                    {MSG_START_SYM,DEVICE_ID_EKG, 0, 0, size},  // header
                    0,                                          // active hours
                    RATE_MIN_SPS,                               // sampling rate
                    GAIN_20_V,                                  // gain
                    DLPF_40_HZ                                  // frequency
                };
                button->setProperty("clicked", false);
                button->setStyleSheet("background-color:rgb(105, 105,105)");
            }else{
                button->setStyleSheet("background-color:rgb(152, 162, 173)");
            }
        }
    }
}

void maindialog::on_ekg_LPfreqBox_currentIndexChanged(int index)
{
    switch (index) {
    case EKG_LP_FREQ_BYPASS:
        configuration_settings.ekg_config.ekg_lowpassFreq= DLPF_BYPASS;
        break;
    case EKG_LP_FREQ_40HZ:
        configuration_settings.ekg_config.ekg_lowpassFreq= DLPF_40_HZ;
        break;
    case EKG_LP_FREQ_100HZ:
        configuration_settings.ekg_config.ekg_lowpassFreq= DLPF_100_HZ;
        break;
    case EKG_LP_FREQ_150HZ:
        configuration_settings.ekg_config.ekg_lowpassFreq= DLPF_150_HZ;
        break;
    }
    qDebug() << configuration_settings.ekg_config.ekg_lowpassFreq << endl;

}



void maindialog::on_ekg_timeclear_button_clicked()
{
    for(QPushButton* button : ui->ekgConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            configuration_settings.ekg_config.ekg_activeHour = 0;
            button->setProperty("clicked", false);
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
        }
    }
    qDebug() << "ekg time is :" << configuration_settings.ekg_config.ekg_activeHour << endl;
}

