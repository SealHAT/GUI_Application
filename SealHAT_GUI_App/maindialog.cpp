#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>

#include <QDebug>

/**
 * Initial GUI setup.
 **/
maindialog::maindialog(QWidget *parent) : QDialog(parent), ui(new Ui::maindialog)
{
    ui->setupUi(this);

    // On the Login stack, set the welcome page.
    ui->loginStacked->setCurrentIndex(INITIAL_PAGE);

    // Set size for smaller welcome screen.
    this->setFixedSize(421, 421);
}

/**
 * Delete GUI on exit.
 **/
maindialog::~maindialog()
{
    delete ui;
}

/**
 * @brief maindialog::on_signOutButton_clicked
 */
void maindialog::on_backButton_clicked()
{
    // Sets the dialog back to a login screen
    this->setFixedSize(421, 421);

    ui->mainStacked->setCurrentIndex(0);
    ui->loginStacked->setCurrentIndex(INITIAL_PAGE);

    this->centerDialog();
}

/**
 * Center the contents of the page.
 **/
void maindialog::centerDialog() {
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}

void maindialog::on_configureHomeButton_clicked()
{
    ui->ConfigurePages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
}

void maindialog::setActiveButtonColor(CONFIGURE_PAGES pageToHighlight)
{
    switch(pageToHighlight)
    {
        case GPS_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(241, 181, 33)");
            ui->imuButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case IMU_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->imuButton->setStyleSheet("background-color:rgb(241, 181, 33)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case EKG_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(241, 181, 33)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->imuButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case TEMPERATURE_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->imuButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(241, 181, 33)");
        } break;
        case LIGHT_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->imuButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(241, 181, 33)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case CONFIGURE_DEV_HOME_PAGE: break;
    }
}

void maindialog::on_lightButton_clicked()
{
    //set button colors. selected tab will be highlighted
    setActiveButtonColor(LIGHT_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(LIGHT_CONFIGURE);
}

void maindialog::on_temperatureButton_clicked()
{
    //set button colors. selected tab will be highlighted
    setActiveButtonColor(TEMPERATURE_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(TEMPERATURE_CONFIGURE);
}

void maindialog::on_ekgButton_clicked()
{
    //set button colors. selected tab will be highlighted
    setActiveButtonColor(EKG_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(EKG_CONFIGURE);
}

void maindialog::on_imuButton_clicked()
{
    //set button colors. selected tab will be highlighted
    setActiveButtonColor(IMU_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(IMU_CONFIGURE);
}

void maindialog::on_gpsButton_clicked()
{
    //set button colors. selected tab will be highlighted
    setActiveButtonColor(GPS_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(GPS_CONFIGURE);
}
