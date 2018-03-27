/**
 *
 */

#include "maindialog.h"
#include "ui_maindialog.h"

void maindialog::on_configureDevOptionButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(1);
    ui->customerPages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
    ui->loggedInUsername->setText("Banana Slug");
    this->centerDialog();

}

void maindialog::on_retrieveDataButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(2);
    ui->customerPages->setCurrentIndex(RETRIEVE_DATA_HOME_PAGE);
    ui->loggedInUsername->setText("Banana Slug");
    this->centerDialog();
}

void maindialog::on_createAccountButton_clicked()
{
    ui->loginStacked->setCurrentIndex(INITIAL_PAGE);
}

void maindialog::on_goBackButton_clicked()
{
    // Sets an previous data that was left on the login screen to be cleared
    // allowing the user to input their new data from their sign up session.
    ui->usernameLogin->clear();
    ui->passwordLogin->clear();

    ui->loginStacked->setCurrentIndex(INITIAL_PAGE);
}


