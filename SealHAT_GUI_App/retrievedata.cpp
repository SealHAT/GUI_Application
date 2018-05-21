#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

void maindialog::on_backButton_retrieveData_clicked()
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
