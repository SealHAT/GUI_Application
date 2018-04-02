#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>

#include <QDebug>

/**************************************************************
 * FUNCTION: on_backButton_clicked
 * ------------------------------------------------------------
 * This function gets called when the Back Button is pressed
 * from any of the Device Configure pages. It sets the active
 * page to the Welcome Page.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::on_backButton_clicked()
{
    // Sets the dialog back to a login screen
    this->setFixedSize(421, 421);

    ui->mainStacked->setCurrentIndex(0);
    ui->StartPageStacked->setCurrentIndex(INITIAL_PAGE);

    this->centerDialog();
}

/**************************************************************
 * FUNCTION: on_configureHomeButton_clicked
 * ------------------------------------------------------------
 * This function gets called when the Configure Home Button is
 * pressed. It sets the active page to the Configure Device
 * Home page. On this page, battery life and storage estimates
 * may be seen.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::on_configureHomeButton_clicked()
{
    //set button colors. selected tab will be highlighted
    setActiveButtonColor(CONFIGURE_DEV_HOME_PAGE);

    ui->ConfigurePages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
}

/**************************************************************
 * FUNCTION: on_lightButton_clicked
 * ------------------------------------------------------------
 * This function gets called when the Light Button is pressed.
 * It sets the active page to the Configure Light Sensor page.
 * On this page, different attributes of the light sensor may
 * be set.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
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
        case CONFIGURE_DEV_HOME_PAGE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->imuButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
    }
}
