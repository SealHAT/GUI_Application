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

void maindialog::temp_disable(bool disable)
{
    temp_disable_button(disable);
    ui->temp_freq->setDisabled(disable);
}

void maindialog::temp_disable_button(bool disable)
{
    ui->b->setDisabled(disable);
    ui->b_2->setDisabled(disable);
    ui->b_3->setDisabled(disable);
    ui->b_4->setDisabled(disable);
    ui->b_5->setDisabled(disable);
    ui->b_6->setDisabled(disable);
    ui->b_7->setDisabled(disable);
    ui->b_8->setDisabled(disable);
    ui->b_9->setDisabled(disable);
    ui->b_10->setDisabled(disable);
    ui->b_11->setDisabled(disable);
    ui->b_12->setDisabled(disable);
    ui->b_13->setDisabled(disable);
    ui->b_14->setDisabled(disable);
    ui->b_15->setDisabled(disable);
    ui->b_16->setDisabled(disable);
    ui->b_17->setDisabled(disable);
    ui->b_18->setDisabled(disable);
    ui->b_19->setDisabled(disable);
    ui->b_20->setDisabled(disable);
    ui->b_21->setDisabled(disable);
    ui->b_22->setDisabled(disable);
    ui->b_23->setDisabled(disable);
    ui->b_24->setDisabled(disable);

    ui->b->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_2->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_3->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_4->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_5->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_6->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_7->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_8->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_9->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_10->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_11->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_12->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_13->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_14->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_15->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_16->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_17->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_18->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_19->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_20->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_21->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_22->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_23->setStyleSheet("background-color:rgb(152, 162, 173)");
    ui->b_24->setStyleSheet("background-color:rgb(152, 162, 173)");
}


void maindialog::temp_timeTable_control()
{
    connect( ui->b, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_2, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_3, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_4, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_5, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_6, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_7, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_8, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_9, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_10, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_11, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_12, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_13, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_14, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_15, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_16, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_17, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_18, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_19, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_20, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_21, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_22, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_23, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_24, SIGNAL(clicked()), this, SLOT(hour_clicked()));

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
