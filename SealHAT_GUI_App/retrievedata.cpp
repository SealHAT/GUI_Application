#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <Qdir>
#include <QFile>
#include "maindialog.h"
#include "ui_maindialog.h"

void maindialog::on_backButton_retrieveData_clicked()
{
    on_backButton_clicked();
}

void maindialog::on_storeData_destinationEdit_editingFinished()
{
   /* QString path = "/c/User/hpan5/Desktop";
    Qdir dir;
    QFile file(path+"file");
    if(!dir.exits(path)){
        dir.mkpath(path);
        qDebug()<<"Dirctory now exits";
        if(file.Open(QIODevice::ReadWrite)){
            qDebug()<<"file now exists";
        }
    }*/
    //ui->storeData_destinationEdit->setText();
}

void maindialog::on_chooseDestButton_clicked()
{
    QString path = "/c/User/hpan5/Desktop/";
    QDir dir;
    QFile file(path +"file");
    if(!dir.exists(path)){
        dir.mkpath(path);
        qDebug()<<"Dirctory now exits";
        if(file.open(QIODevice::ReadWrite)){
            qDebug()<<"file now exists";
        }
    }
}
