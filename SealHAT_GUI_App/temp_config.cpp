#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>



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

void maindialog::hour_clicked()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!button->property("clicked").isValid()) {
        button->setProperty("clicked", false);
    }
    bool clicked = button->property("clicked").toBool();
    button->setProperty("clicked", !clicked);

    if(!clicked) {
        button->setStyleSheet("background-color:rgb(34,139,34)");
        temporaryTemp.temp_time |= 1 << button->property("button_shift").toInt();
    } else {
        button->setStyleSheet("background-color:rgb(152, 162, 173)");
        temporaryTemp.temp_time &= ~(1 << button->property("button_shift").toInt());
    }
    qDebug() << "time is :" << temporaryTemp.temp_time << endl;
}
