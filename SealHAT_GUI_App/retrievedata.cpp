#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <Qdir>
#include <QFile>
#include <QMessageBox>
#include "maindialog.h"
#include "ui_maindialog.h"

void maindialog::on_backButton_retrieveData_clicked()
{
    on_backButton_clicked();
}

void maindialog::on_storeData_destinationEdit_returnPressed()
{
    QString path = ui->storeData_destinationEdit->text();
     QDir newDir;
     if(!newDir.exists(path)){
         QMessageBox::information(this,tr("created new directory"), path);
         newDir.mkpath(path);
         qDebug()<<"Created new directory";
     }
}

void maindialog::on_chooseDestButton_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory"),
                "C:/Users/hpan5/Downloads",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
            );

    ui->storeData_destinationEdit->setText(dir);

    //
    /*
    QString path = ui->storeData_destinationEdit->text();
    QDir dir;
    QFile file(path +"file");
    if(!dir.exists(path)){
        dir.mkpath(path);
        qDebug()<<"Dirctory now exits";
        if(file.open(QIODevice::ReadWrite)){
            qDebug()<<"file now exists";
        }
    }*/
}


void maindialog::on_getDataButton_clicked()
{
    QString path = ui->storeData_destinationEdit->text();
    QDir dir;

    if(!dir.exists(path)){
        dir.mkpath(path);
        QMessageBox::information(this,tr("created new directory"), path);;
    }
    QFile file(path +"out.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
           return;

       QTextStream out(&file);
       out << "The magic number is: " << 49 << "\n";
}

