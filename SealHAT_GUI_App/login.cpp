/**
 *
 */

#include "maindialog.h"
#include "ui_maindialog.h"

void maindialog::on_configureDevOptionButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(1);
    ui->ConfigurePages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
    this->centerDialog();
}

void maindialog::on_retrieveDataButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(2);
    ui->ConfigurePages->setCurrentIndex(RETRIEVE_DATA_HOME_PAGE);
    this->centerDialog();
}

void maindialog::on_goBackButton_clicked()
{
    ui->loginStacked->setCurrentIndex(INITIAL_PAGE);
}


