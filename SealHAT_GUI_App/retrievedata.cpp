#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>

#include <QDebug>


void maindialog::on_backButton2_clicked()
{
    on_backButton_clicked();
}

void maindialog::on_storeData_destinationEdit_editingFinished()
{
    ui->storeData_destinationEdit->setText("/c/User/hpan5/Desktop");
}

void maindialog::on_chooseDestButton_clicked()
{

}
