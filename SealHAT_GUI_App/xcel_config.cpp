#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

void maindialog::xcel_changeMode()
{
    uint8_t pwrIndex = 0;
    uint8_t freq;

    pwrIndex= ui->xcel_pwrBox->currentIndex();
    freq = ui->xcel_freqBox->currentIndex();

    if(pwrIndex == ACC_LP)
    {
        switch(freq){
        case ACC_FREQ_1HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_LP_1_HZ;
        break;
        case ACC_FREQ_10HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_LP_10_HZ;
        break;
        case ACC_FREQ_25HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_LP_25_HZ;
        break;
        case ACC_FREQ_50HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_LP_50_HZ;
        break;
        case ACC_FREQ_100HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_LP_100_HZ;
        break;
        case ACC_FREQ_200HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_LP_200_HZ;
        break;
        case ACC_FREQ_400HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_LP_400_HZ;
        break;
        }

    }else if(pwrIndex == ACC_NORMAL){
        switch(freq){
        case ACC_FREQ_1HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_NORM_1_HZ;
        break;
        case ACC_FREQ_10HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_NORM_10_HZ;
        break;
        case ACC_FREQ_25HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_NORM_25_HZ;
        break;
        case ACC_FREQ_50HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_NORM_50_HZ;
        break;
        case ACC_FREQ_100HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_NORM_100_HZ;
        break;
        case ACC_FREQ_200HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_NORM_200_HZ;
        break;
        case ACC_FREQ_400HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_NORM_400_HZ;
        break;
        }

    }else if(pwrIndex == ACC_HR){
        switch(freq){
        case ACC_FREQ_1HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_HR_1_HZ;
        break;
        case ACC_FREQ_10HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_HR_10_HZ;
        break;
        case ACC_FREQ_25HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_HR_25_HZ;
        break;
        case ACC_FREQ_50HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_HR_50_HZ;
        break;
        case ACC_FREQ_100HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_HR_100_HZ;
        break;
        case ACC_FREQ_200HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_HR_200_HZ;
        break;
        case ACC_FREQ_400HZ:
            configuration_settings.accelerometer_config.acc_mode = ACC_HR_400_HZ;
        break;
        }
    }
    qDebug() << QString::number(configuration_settings.accelerometer_config.acc_mode, 16) << endl;
}

void maindialog::on_xcel_scaleBox_currentIndexChanged(int index)
{
    switch(index){
    case ACC_2G:    configuration_settings.accelerometer_config.acc_scale = ACC_SCALE_2G;
        break;
    case ACC_4G:    configuration_settings.accelerometer_config.acc_scale = ACC_SCALE_4G;
        break;
    case ACC_8G:    configuration_settings.accelerometer_config.acc_scale = ACC_SCALE_8G;
        break;
    case ACC_16G:    configuration_settings.accelerometer_config.acc_scale = ACC_SCALE_16G;
        break;
    }
}

void maindialog::on_xcel_pwrBox_currentIndexChanged()
{
    xcel_changeMode();
}

void maindialog::on_xcel_freqBox_currentIndexChanged()
{
    xcel_changeMode();
}

void maindialog::on_xcel_XL_checkBox_clicked(bool checked)
{
    //qDebug() << checked << endl;
    ui->xcel_XH_checkBox->setDisabled(checked);
    if(checked){
        configuration_settings.accelerometer_config.acc_sensitivity |= MOTION_INT_X_LOW;
    }else{
        configuration_settings.accelerometer_config.acc_sensitivity &= (~MOTION_INT_X_LOW);
    }
    qDebug() << configuration_settings.accelerometer_config.acc_sensitivity << endl;

}

void maindialog::on_xcel_XH_checkBox_clicked(bool checked)
{
    ui->xcel_XL_checkBox->setDisabled(checked);
    if(checked){
        configuration_settings.accelerometer_config.acc_sensitivity |= MOTION_INT_X_HIGH;
    }else{
        configuration_settings.accelerometer_config.acc_sensitivity &= (~MOTION_INT_X_HIGH);
    }
    qDebug() << configuration_settings.accelerometer_config.acc_sensitivity << endl;
}

void maindialog::on_xcel_YL_checkBox_clicked(bool checked)
{
    ui->xcel_YH_checkBox->setDisabled(checked);
    if(checked){
        configuration_settings.accelerometer_config.acc_sensitivity |= MOTION_INT_Y_LOW;
    }else{
        configuration_settings.accelerometer_config.acc_sensitivity &= (~MOTION_INT_Y_LOW);
    }
    qDebug() << configuration_settings.accelerometer_config.acc_sensitivity << endl;
}

void maindialog::on_xcel_YH_checkBox_clicked(bool checked)
{
    ui->xcel_YL_checkBox->setDisabled(checked);
    if(checked){
        configuration_settings.accelerometer_config.acc_sensitivity |= MOTION_INT_Y_HIGH;
    }else{
        configuration_settings.accelerometer_config.acc_sensitivity &= (~MOTION_INT_Y_HIGH);
    }
    qDebug() << configuration_settings.accelerometer_config.acc_sensitivity << endl;
}

void maindialog::on_xcel_ZL_checkBox_clicked(bool checked)
{
    ui->xcel_ZH_checkBox->setDisabled(checked);
    if(checked){
        configuration_settings.accelerometer_config.acc_sensitivity |= MOTION_INT_Z_LOW;
    }else{
        configuration_settings.accelerometer_config.acc_sensitivity &= (~MOTION_INT_Z_LOW);
    }
    qDebug() << configuration_settings.accelerometer_config.acc_sensitivity << endl;
}

void maindialog::on_xcel_ZH_checkBox_clicked(bool checked)
{
    ui->xcel_ZL_checkBox->setDisabled(checked);
    if(checked){
        configuration_settings.accelerometer_config.acc_sensitivity |= MOTION_INT_Z_HIGH;
    }else{
        configuration_settings.accelerometer_config.acc_sensitivity &= (~MOTION_INT_Z_HIGH);
    }
    qDebug() << configuration_settings.accelerometer_config.acc_sensitivity << endl;
}

/* Enable/Disable xcel sensor.
 * Disable all the configuration option if this button is clicked.
*/
void maindialog::IMUxcel_Disable(bool disable)
{
    ui->xcel_timeclear_button->setDisabled(disable);
    ui->xcel_scaleBox->setDisabled(disable);
    ui->xcel_pwrBox->setDisabled(disable);
    ui->xcel_freqBox->setDisabled(disable);
    ui->xcel_XL_checkBox->setDisabled(disable);
    ui->xcel_XH_checkBox->setDisabled(disable);
    ui->xcel_YL_checkBox->setDisabled(disable);
    ui->xcel_YH_checkBox->setDisabled(disable);
    ui->xcel_ZL_checkBox->setDisabled(disable);
    ui->xcel_ZH_checkBox->setDisabled(disable);
    ui->xcel_thres->setDisabled(disable);
    if(disable){
        ui->thres_warnLABEL->setVisible(!disable);
    }
}

void maindialog::xcel_setDefault()
{
    on_xcel_timeclear_button_clicked();
    ui->xcel_scaleBox->setCurrentIndex(ACC_2G);
    ui->xcel_pwrBox->setCurrentIndex(ACC_HR);
    ui->xcel_freqBox->setCurrentIndex(ACC_FREQ_50HZ);
    ui->xcel_thres->setText("0.5");
    uint16_t size = sizeof(ACC_FULL_SCALE_t) + sizeof(ACC_OPMODE_t) + 2*sizeof(uint8_t) + sizeof(uint16_t);

    configuration_settings.accelerometer_config = {
        {MSG_START_SYM, DEVICE_ID_ACCELEROMETER, 0, 0, size},   // header
        0,                                                      // active hours
        ACC_SCALE_2G,                                           // scale
        ACC_HR_50_HZ,                                           // mode
        0x00,                                                   // sensitivity
        300,                                                    // threshold
        0                                                       // duration
    };
}

void maindialog::on_xcel_SW_clicked()
{
    QString title = ui->xcel_SW->text();
    if(title == "Enable")
    {
        ui->xcel_SW->setText("Disable");
        IMUxcel_Disable(false);
        xcel_disable_button(false);
    }else{
        ui->xcel_SW->setText("Enable");
        IMUxcel_Disable(true);
        xcel_disable_button(true);
    }
}

void maindialog::on_xcel_timeclear_button_clicked()
{
    for(QPushButton* button : ui->xcelConfigPage->findChildren<QPushButton*>()) {
        if(button->property("button_shift").isValid()) {
            configuration_settings.accelerometer_config.xcel_activeHour = 0;
            button->setProperty("clicked", false);
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            }
        }
    qDebug() << "xcel time is :" << configuration_settings.accelerometer_config.xcel_activeHour << endl;
}

/*Check the value in duration blank and enable the warning
 * if the value user put in is not is the range [0.32, 128] with
 * less than or equal to 5 digits after the decimal point
*/



/*Check the value in threshold blank and enable the warning
 * if the value user put in is not is the range [0,16] with
 * less than or equal to 5 digits after the decimal point
*/
void maindialog::on_xcel_thres_editingFinished()
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::WindowText, Qt::red);

    int valid;
    int pos;

    if(ui->xcel_scaleBox->currentIndex() == ACC_2G)
    {
        QDoubleValidator v(0, 2, 5,this);
        QString thres = ui->xcel_thres->text();
        valid = v.validate(thres, pos);
        ui->thres_warnLABEL->setText("Invalid threshold value! (0-2)");

    }else if(ui->xcel_scaleBox->currentIndex() == ACC_4G)
    {
        QDoubleValidator v(0, 4, 5,this);
        QString thres = ui->xcel_thres->text();
        valid = v.validate(thres, pos);
        ui->thres_warnLABEL->setText("Invalid threshold value! (0-4)");
    }else if(ui->xcel_scaleBox->currentIndex() == ACC_8G)
    {
        QDoubleValidator v(0, 8, 5,this);
        QString thres = ui->xcel_thres->text();
        valid = v.validate(thres, pos);
        ui->thres_warnLABEL->setText("Invalid threshold value! (0-8)");
    }else if(ui->xcel_scaleBox->currentIndex() == ACC_16G)
    {
        QDoubleValidator v(0, 16, 5,this);
        QString thres = ui->xcel_thres->text();
        valid = v.validate(thres, pos);
        ui->thres_warnLABEL->setText("Invalid threshold value! (0-16)");
    }
    ui->thres_warnLABEL->setAutoFillBackground(true);
    ui->thres_warnLABEL->setPalette(sample_palette);

    if(valid != ACCEPTABLE){
        ui->thres_warnLABEL->show();
    }else{
        ui->thres_warnLABEL->hide();
    }

}


void maindialog::xcel_hour_clicked()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!button->property("clicked").isValid()) {
        button->setProperty("clicked", false);
    }
    bool clicked = button->property("clicked").toBool();
    button->setProperty("clicked", !clicked);
        if(!clicked) {
            button->setStyleSheet("background-color:rgb(34,139,34)");
            configuration_settings.accelerometer_config.xcel_activeHour |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            configuration_settings.accelerometer_config.xcel_activeHour &= ~(1 << button->property("button_shift").toInt());
        }

        qDebug() << "xcel time is :" << configuration_settings.accelerometer_config.xcel_activeHour << endl;

}


void maindialog::xcel_timeTable_control()
{
    for(QPushButton* button : ui->xcelConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            connect(button,SIGNAL(clicked()), this, SLOT(xcel_hour_clicked()));
        }
    }
}


void maindialog::xcel_disable_button(bool disable)
{
    for(QPushButton* button : ui->xcelConfigPage->findChildren<QPushButton*>()) {
        if(button->property("button_shift").isValid()) {
            button->setDisabled(disable);
            if(disable){
                configuration_settings.accelerometer_config.xcel_activeHour = 0;
                configuration_settings.accelerometer_config.acc_mode = ACC_POWER_DOWN;
                button->setProperty("clicked", false);
                button->setStyleSheet("background-color:rgb(105, 105,105)");
            }else{
                button->setStyleSheet("background-color:rgb(152, 162, 173)");
            }
        }
    }
}
