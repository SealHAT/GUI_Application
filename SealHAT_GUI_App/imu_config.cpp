#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QDebug>
/*
void maindialog::on_pushButton_clicked()
{
    QString tempString = ui->Fillin->text();

    if(ui->Fillin->text() == "DORIS")
    {
        ui->yay_label->show();
    }
    else
    {
        ui->yay_label->hide();
    }
}

void maindialog::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0);
}*/
/*
void maindialog::on_lineEdit_2_editingFinished()
{
    int valid;

    QString thres = ui->xcel_thres->text();
    QDoubleValidator v(16, 0, 10,this);
    v.validate(thres, valid);
    ui->warn_label->hide();
    if(valid != 2){
        ui->warn_label->show();
    }else{
    ui->warn_label->hide();
    }
}*/

void maindialog::on_xcel_thres_returnPressed()
{
    int valid;
    QIntValidator v(1, 5, this);
    //QDoubleValidator v(16, 0, 0,this);
    QString thres = ui->xcel_thres->text();
    //QString thres;

    v.validate(thres, valid);

    if(valid != 2){
        ui->warn_label->setText((QString)valid);
        ui->warn_label->show();
    }else{
    ui->warn_label->hide();
    }
}
