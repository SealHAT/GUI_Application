
#include "maindialog.h"
#include "ui_maindialog.h"

/**
 * All functionality corresponding to login,
 * such as:
 *
 * encrypting,
 * error checking for login,
 * creating an account,
 * signals from the page login or sign up,
 * etc.
 *
 * will be located here.
 */

bool maindialog::isBlank(QString text) {
    return text.trimmed() == "";
}

void maindialog::on_configureDevOptionButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(1);
    ui->customerPages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
    ui->loggedInUsername->setText("Banana Slug");
    this->centerDialog();

}

void maindialog::on_signUpButton_clicked()
{
    // Set the go back button the 'rewind44.png'
    QPixmap pixmap(":/rewind44.png");
    QIcon ButtonIcon(pixmap);
    ui->goBackButton->setIcon(ButtonIcon);
    ui->goBackButton->setIconSize(ui->goBackButton->rect().size());

    // Sets and clears all input fields,
    // along with hidding error message until given the trigger to do so.
    ui->usernameError->setHidden(true);
    ui->passwordError->setHidden(true);
    ui->retryPasswordError->setHidden(true);
    ui->termsAndConditionsError->setHidden(true);

    if(!isBlank(ui->usernameLogin->text())) {
        ui->newUsername->setText(ui->usernameLogin->text());
    }
    else {
        ui->newUsername->clear();
    }

    ui->newPassword->clear();
    ui->retryPassword->clear();
    ui->agreementCheckBox->setChecked(false);


    ui->loginStacked->setCurrentIndex(SIGN_UP_PAGE);
}


void maindialog::on_createAccountButton_clicked()
{
    ui->usernameError->setVisible(false);
        ui->passwordError->setVisible(false);
        ui->retryPasswordError->setVisible(false);
        ui->termsAndConditionsError->setVisible(false);

        QString username  = ui->newUsername->text();
        QString password  = ui->newPassword->text();
        QString retryPass = ui->retryPassword->text();

        bool isValid = true;

        // Error checking for creating a new account

        // Checks if the username is already taken.
        if((_customerList.isUniqueUsername(username))) {
            ui->usernameError->setText("Username is already taken.");
            ui->usernameError->setVisible(true);
            isValid = false;
        }

        // Checks if the terms and conditions agreement check box was checked or left unchecked.
        if(!ui->agreementCheckBox->isChecked()) {
            ui->termsAndConditionsError->setText("Terms and conditions was left unchecked.");
            ui->termsAndConditionsError->setVisible(true);
            isValid = false;
        }

        if(isBlank(username)) {
            ui->usernameError->setText("Username was left blank.");
            ui->usernameError->setVisible(true);
            isValid = false;
        }

        if(isBlank(password)) {
            ui->passwordError->setText("Password was left blank.");
            ui->passwordError->setVisible(true);
            isValid = false;
        }

        if(isBlank(retryPass)) {
            ui->retryPasswordError->setText("Re-enter password was left blank.");
            ui->retryPasswordError->setVisible(true);
            isValid = false;
        }

        if(password != retryPass) {
            ui->passwordError->setText("Passwords do not match.");
            ui->passwordError->setVisible(true);
            isValid = false;
        }

        if(isValid) {
            _customerList.addCustomer(username, password);
            _sql.addAccount(new Account(username, password));

            ui->loginStacked->setCurrentIndex(INITIAL_PAGE);
        }

}

void maindialog::on_goBackButton_clicked()
{
    // Sets an previous data that was left on the login screen to be cleared
    // allowing the user to input their new data from their sign up session.
    ui->usernameLogin->clear();
    ui->passwordLogin->clear();
    ui->loginErrorMessage->setVisible(false);

    ui->loginStacked->setCurrentIndex(INITIAL_PAGE);
}


