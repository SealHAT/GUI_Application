#include "maindialog.h"
#include "ui_maindialog.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>

/* Enable/Disable xcel sensor.
 * Disable all the configuration option if this button is clicked.
*/

/*void maindialog::IMUxcel_collectdata(bool disable)
{
    Xcel xcel;
    xcel = {0, 0, 0, 0};

    if(ui->xcel_sixD_button->isChecked())
    {
        xcel.mode |= ACC_6D_ENABLE;
    }else if(ui->xcel_fourD_button->isChecked())
    {
        xcel.mode |= ACC_4D_ENABLE;
    }

    if(ui->xcel_scaleBox->currentIndex() == ACC_2G)
    {
        xcel.mode |= ACC_2G_SCALE;
    }else if(ui->xcel_scaleBox->currentIndex() == ACC_4G)
    {
        xcel.mode |= ACC_4G_SCALE;
    }else if(ui->xcel_scaleBox->currentIndex() == ACC_8G)
    {
        xcel.mode |= ACC_8G_SCALE;
    }

    if(ui->xcel_pwrBox->currentIndex() == ACC_HR)
    {
        xcel.mode |= ACC_HR_PWR;
    }else if(ui->xcel_pwrBox->currentIndex() == ACC_NORMAL)
    {
        xcel.mode |= ACC_NORM_PWR;
    }else if(ui->xcel_pwrBox->currentIndex() == ACC_LP)
    {
        xcel.mode |= ACC_LP_PWR;
    }

    if(ui->xcel_freqBox->currentIndex() == FREQ_1HZ)
    {
        xcel.mode |= ACC_1HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_10HZ)
    {
        xcel.mode |= ACC_10HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_25HZ)
    {
        xcel.mode |= ACC_25HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_50HZ)
    {
        xcel.mode |= ACC_50HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_100HZ)
    {
        xcel.mode |= ACC_100HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_200HZ)
    {
        xcel.mode |= ACC_200HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_400HZ)
    {
        xcel.mode |= ACC_400HZ_FREQ;
    }

    xcel.threshold = (ui->xcel_thres->text()).toUInt()/(0.016);
    xcel.duration = (ui->xcel_duration->text()).toUInt();
    qDebug() << QString("mode:") << quint8(xcel.mode) << endl;
    //QDebug() << "thres:" << quint8(xcel.threshold) << endl;
    //QDebug() << "duration:" << quint8(xcel.duration) << endl;
    //store xcel value
}*/

void maindialog::IMUxcel_Disable(bool disable)
{
    ui->xcel_scaleBox->setDisabled(disable);
    ui->xcel_pwrBox->setDisabled(disable);
    ui->xcel_freqBox->setDisabled(disable);
    ui->xcel_sixD_button->setDisabled(disable);
    ui->xcel_fourD_button->setDisabled(disable);
    ui->xcel_thres->setDisabled(disable);
    ui->xcel_duration->setDisabled(disable);
    if(disable){
        ui->thres_warnLABEL->setVisible(!disable);
        ui->dur_warnLABEL->setVisible(!disable);
    }
}

void maindialog::xcel_setDefault()
{
    ui->xcel_scaleBox->setCurrentIndex(ACC_2G);
    ui->xcel_pwrBox->setCurrentIndex(ACC_HR);
    ui->xcel_freqBox->setCurrentIndex(ACC_FREQ_50HZ);
    ui->xcel_thres->setText("0.5");
    ui->xcel_duration->setText("0");
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
    xcel_disable_button(true);
}

/*Check the value in threshold blank and enable the warning
 * if the value user put in is not is the range [0,16] with
 * less than or equal to 5 digits after the decimal point
*/
void maindialog::on_xcel_thres_editingFinished()
{
    int valid;
    int pos;
    QDoubleValidator v(0, 16, 5,this);

    QString thres = ui->xcel_thres->text();
    valid = v.validate(thres, pos);

    if(valid != ACCEPTABLE){
        ui->thres_warnLABEL->show();
    }else{
        ui->thres_warnLABEL->hide();
    }
}

/*Check the value in duration blank and enable the warning
 * if the value user put in is not is the range [0.32, 128] with
 * less than or equal to 5 digits after the decimal point
*/
void maindialog::on_xcel_duration_editingFinished()
{
    int valid;
    int pos;
    QDoubleValidator v(0.32, 128, 5,this);

    QString thres = ui->xcel_duration->text();
    valid = v.validate(thres, pos);
    qDebug() << valid;
    if(valid != ACCEPTABLE){
        ui->dur_warnLABEL->show();

    }else{
        ui->dur_warnLABEL->hide();
    }
}



void maindialog::xcel_timeTable_control()
{
    for(QPushButton* button : ui->xcelConfigPage->findChildren<QPushButton*>())
    {
        if(button->property("button_shift").isValid())
        {
            connect(button,SIGNAL(clicked()), this, SLOT(hour_clicked()));
        }
    }
}


void maindialog::xcel_disable_button(bool disable)
{
    for(QPushButton* button : ui->xcelConfigPage->findChildren<QPushButton*>()) {
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

/*
void maindialog::on_xcel_finishButton_clicked()
{
    Xcel xcel;
    xcel = {0, 0, 0, 0};

    if(ui->xcel_sixD_button->isChecked())
    {
        xcel.mode |= ACC_6D_ENABLE;
    }else if(ui->xcel_fourD_button->isChecked())
    {
        xcel.mode |= ACC_4D_ENABLE;
    }

    if(ui->xcel_scaleBox->currentIndex() == ACC_2G)
    {
        xcel.mode |= ACC_2G_SCALE;
    }else if(ui->xcel_scaleBox->currentIndex() == ACC_4G)
    {
        xcel.mode |= ACC_4G_SCALE;
    }else if(ui->xcel_scaleBox->currentIndex() == ACC_8G)
    {
        xcel.mode |= ACC_8G_SCALE;
    }

    if(ui->xcel_pwrBox->currentIndex() == ACC_HR)
    {
        xcel.mode |= ACC_HR_PWR;
    }else if(ui->xcel_pwrBox->currentIndex() == ACC_NORMAL)
    {
        xcel.mode |= ACC_NORM_PWR;
    }else if(ui->xcel_pwrBox->currentIndex() == ACC_LP)
    {
        xcel.mode |= ACC_LP_PWR;
    }

    if(ui->xcel_freqBox->currentIndex() == FREQ_1HZ)
    {
        xcel.mode |= ACC_1HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_10HZ)
    {
        xcel.mode |= ACC_10HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_25HZ)
    {
        xcel.mode |= ACC_25HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_50HZ)
    {
        xcel.mode |= ACC_50HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_100HZ)
    {
        xcel.mode |= ACC_100HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_200HZ)
    {
        xcel.mode |= ACC_200HZ_FREQ;
    }else if(ui->xcel_freqBox->currentIndex() == FREQ_400HZ)
    {
        xcel.mode |= ACC_400HZ_FREQ;
    }

    xcel.threshold = (ui->xcel_thres->text()).toUInt()/(0.016);
    xcel.duration = (ui->xcel_duration->text()).toUInt();
    qDebug() << QString("mode:") << quint8(xcel.mode) << endl;
    //QDebug() << "thres:" << quint8(xcel.threshold) << endl;
    //QDebug() << "duration:" << quint8(xcel.duration) << endl;
    //store xcel value
}*/

