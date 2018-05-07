#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>

/* Enable/Disable GPS sensor.
 * Disable all the configuration option if this button is clicked.
*/

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
    ui->gps_b->setDisabled(disable);
    ui->gps_b_2->setDisabled(disable);
    ui->gps_b_3->setDisabled(disable);
    ui->gps_b_4->setDisabled(disable);
    ui->gps_b_5->setDisabled(disable);
    ui->gps_b_6->setDisabled(disable);
    ui->gps_b_7->setDisabled(disable);
    ui->gps_b_8->setDisabled(disable);
    ui->gps_b_9->setDisabled(disable);
    ui->gps_b_10->setDisabled(disable);
    ui->gps_b_11->setDisabled(disable);
    ui->gps_b_12->setDisabled(disable);
    ui->gps_b_13->setDisabled(disable);
    ui->gps_b_14->setDisabled(disable);
    ui->gps_b_15->setDisabled(disable);
    ui->gps_b_16->setDisabled(disable);
    ui->gps_b_17->setDisabled(disable);
    ui->gps_b_18->setDisabled(disable);
    ui->gps_b_19->setDisabled(disable);
    ui->gps_b_20->setDisabled(disable);
    ui->gps_b_21->setDisabled(disable);
    ui->gps_b_22->setDisabled(disable);
    ui->gps_b_23->setDisabled(disable);
    ui->gps_b_24->setDisabled(disable);

    ui->gps_b->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_2->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_3->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_4->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_5->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_6->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_7->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_8->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_9->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_10->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_11->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_12->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_13->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_14->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_15->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_16->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_17->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_18->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_19->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_20->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_21->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_22->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_23->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->gps_b_24->setStyleSheet("background-color:rgb(152, 162, 173)");
}

void maindialog::gps_timeTable_control()
{
        connect( ui->gps_b, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_2, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_3, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_4, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_5, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_6, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_7, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_8, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_9, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_10, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_11, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_12, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_13, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_14, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_15, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_16, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_17, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_18, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_19, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_20, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_21, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_22, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_23, SIGNAL(clicked()), this, SLOT(hour_clicked()));
        connect( ui->gps_b_24, SIGNAL(clicked()), this, SLOT(hour_clicked()));

}
