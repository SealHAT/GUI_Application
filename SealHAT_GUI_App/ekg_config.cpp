#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>

/* Enable/Disable Ekg sensor.
 * Disable all the configuration option if this button is clicked.
*/

void maindialog::ekg_Disable(bool disable)
{
    ui->ekg_freqBox->setDisabled(disable);
    ui->ekg_gainBox->setDisabled(disable);
    ui->ekg_LPfreqBox->setDisabled(disable);
    ekg_disable_button(disable);
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

void maindialog::ekg_disable_button(bool disable)
{
    ui->ekg_b->setDisabled(disable);
    ui->ekg_b_2->setDisabled(disable);
    ui->ekg_b_3->setDisabled(disable);
    ui->ekg_b_4->setDisabled(disable);
    ui->ekg_b_5->setDisabled(disable);
    ui->ekg_b_6->setDisabled(disable);
    ui->ekg_b_7->setDisabled(disable);
    ui->ekg_b_8->setDisabled(disable);
    ui->ekg_b_9->setDisabled(disable);
    ui->ekg_b_10->setDisabled(disable);
    ui->ekg_b_11->setDisabled(disable);
    ui->ekg_b_12->setDisabled(disable);
    ui->ekg_b_13->setDisabled(disable);
    ui->ekg_b_14->setDisabled(disable);
    ui->ekg_b_15->setDisabled(disable);
    ui->ekg_b_16->setDisabled(disable);
    ui->ekg_b_17->setDisabled(disable);
    ui->ekg_b_18->setDisabled(disable);
    ui->ekg_b_19->setDisabled(disable);
    ui->ekg_b_20->setDisabled(disable);
    ui->ekg_b_21->setDisabled(disable);
    ui->ekg_b_22->setDisabled(disable);
    ui->ekg_b_23->setDisabled(disable);
    ui->ekg_b_24->setDisabled(disable);

    ui->ekg_b->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_2->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_3->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_4->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_5->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_6->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_7->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_8->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_9->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_10->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_11->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_12->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_13->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_14->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_15->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_16->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_17->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_18->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_19->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_20->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_21->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_22->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_23->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->ekg_b_24->setStyleSheet("background-color:rgb(152, 162, 173)");

}

void maindialog::ekg_timeTable_control()
{
        connect( ui->ekg_b, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_2, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_3, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_4, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_5, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_6, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_7, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_8, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_9, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_10, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_11, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_12, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_13, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_14, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_15, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_16, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_17, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_18, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_19, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_20, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_21, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_22, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_23, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->ekg_b_24, SIGNAL(clicked()), this, SLOT(hour_clicked()));

}
