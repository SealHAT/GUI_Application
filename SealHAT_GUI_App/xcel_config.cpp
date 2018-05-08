#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>

/* Enable/Disable xcel sensor.
 * Disable all the configuration option if this button is clicked.
*/

void maindialog::IMUxcel_Disable()
{
    ui->xcel_scaleBox->setDisabled(true);
    ui->xcel_pwrBox->setDisabled(true);
    ui->xcel_freqBox->setDisabled(true);
    ui->xcel_sixD_button->setDisabled(true);
    ui->xcel_fourD_button->setDisabled(true);
    ui->xcel_thres->setDisabled(true);
    ui->xcel_duration->setDisabled(true);
    //ui->xcel_finishButton->setDisabled(true);
    ui->thres_warnLABEL->hide();
    ui->dur_warnLABEL->hide();
}

void maindialog::IMUxcel_Enable()
{
    ui->xcel_scaleBox->setDisabled(false);
    ui->xcel_pwrBox->setDisabled(false);
    ui->xcel_freqBox->setDisabled(false);
    ui->xcel_sixD_button->setDisabled(false);
    ui->xcel_fourD_button->setDisabled(false);
    ui->xcel_thres->setDisabled(false);
    ui->xcel_duration->setDisabled(false);
    //ui->xcel_finishButton->setDisabled(false);
}


void maindialog::on_IMU_SW_clicked()
{
    QString title = ui->IMU_SW->text();
    if(title == "Enable")
    {
        ui->IMU_SW->setText("Disable");
        ui->xcel_SW->setDisabled(false);
        //ui->mag_SW->setDisabled(false);
        IMUxcel_Enable();
        IMUmag_Enable();
    }else{
        ui->IMU_SW->setText("Enable");
        ui->xcel_SW->setDisabled(true);
        //ui->mag_SW->setDisabled(true);
        IMUxcel_Disable();
        IMUmag_Disable();
    }
}


void maindialog::on_xcel_SW_clicked()
{
    QString title = ui->xcel_SW->text();
    if(title == "Enable")
    {
        ui->xcel_SW->setText("Disable");
        IMUxcel_Enable();
        xcel_disable_button(false);
    }else{
        ui->xcel_SW->setText("Enable");
        IMUxcel_Disable();
        xcel_disable_button(true);
    }
}

/*
void maindialog::on_mag_SW_clicked()
{
    QString title = ui->mag_SW->text();
    if(title == "Enable")
    {
        ui->mag_SW->setText("Disable");
        IMUmag_Enable();
    }else{
        ui->mag_SW->setText("Enable");
        IMUmag_Disable();
    }
}*/



/*Switch from MAG to ACC*/
/*void maindialog::on_Xcel_swPAGE_clicked()
{
    //setActiveButtonColor(MAG_CONFIGURE);

    ui->imuPages->setCurrentIndex(XCEL_CONFIGURE);
}*/

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

void maindialog::xcel_timeTable_control()
{
        connect( ui->xcel_b, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_2, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_3, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_4, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_5, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_6, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_7, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_8, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_9, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_10, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_11, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_12, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_13, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_14, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_15, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_16, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_17, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_18, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_19, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_20, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_21, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_22, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_23, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->xcel_b_24, SIGNAL(clicked()), this, SLOT(hour_clicked()));

}


void maindialog::xcel_disable_button(bool disable)
{
    ui->xcel_b->setDisabled(disable);
    ui->xcel_b_2->setDisabled(disable);
    ui->xcel_b_3->setDisabled(disable);
    ui->xcel_b_4->setDisabled(disable);
    ui->xcel_b_5->setDisabled(disable);
    ui->xcel_b_6->setDisabled(disable);
    ui->xcel_b_7->setDisabled(disable);
    ui->xcel_b_8->setDisabled(disable);
    ui->xcel_b_9->setDisabled(disable);
    ui->xcel_b_10->setDisabled(disable);
    ui->xcel_b_11->setDisabled(disable);
    ui->xcel_b_12->setDisabled(disable);
    ui->xcel_b_13->setDisabled(disable);
    ui->xcel_b_14->setDisabled(disable);
    ui->xcel_b_15->setDisabled(disable);
    ui->xcel_b_16->setDisabled(disable);
    ui->xcel_b_17->setDisabled(disable);
    ui->xcel_b_18->setDisabled(disable);
    ui->xcel_b_19->setDisabled(disable);
    ui->xcel_b_20->setDisabled(disable);
    ui->xcel_b_21->setDisabled(disable);
    ui->xcel_b_22->setDisabled(disable);
    ui->xcel_b_23->setDisabled(disable);
    ui->xcel_b_24->setDisabled(disable);

    ui->xcel_b->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_2->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_3->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_4->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_5->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_6->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_7->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_8->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_9->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_10->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_11->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_12->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_13->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_14->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_15->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_16->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_17->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_18->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_19->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_20->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_21->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_22->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_23->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->xcel_b_24->setStyleSheet("background-color:rgb(152, 162, 173)");
}





/*
void maindialog::setActiveIMU_PAGEColor(IMU_MODE Mode)
{
    switch(Mode)
    {
        case ENABLE: {
            //ui->xcelConfigPage->setStyleSheet("background-color:rgb(152, 162, 173)");
            //ui->magConfigPage->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case DISABLE: {
            //ui->xcelConfigPage->setStyleSheet("background-color:black;");
            //ui->magConfigPage->setStyleSheet("background-color:black;");
        } break;
    }
}*/


