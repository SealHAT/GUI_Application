#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>

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

