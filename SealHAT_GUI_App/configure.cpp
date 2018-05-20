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

void maindialog::goto_DEV()
{

    setActiveButtonColor(CONFIGURE_DEV_HOME_PAGE);

    ui->ConfigurePages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
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

/**************************************************************
 * FUNCTION: on_temperatureButton_clicked
 * ------------------------------------------------------------
 * This function gets called when the Temperature Button is
 * pressed. It sets the active page to the Configure
 * Temperature Sensor page. On this page, different attributes
 * of the temperature sensor may be set.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::on_temperatureButton_clicked()
{
    //set button colors. selected tab will be highlighted
    setActiveButtonColor(TEMPERATURE_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(TEMPERATURE_CONFIGURE);
}

/**************************************************************
 * FUNCTION: on_ekgButton_clicked
 * ------------------------------------------------------------
 * This function gets called when the EKG Button is pressed. It
 * sets the active page to the Configure EKG Sensor page. On
 * this page, different attributes of the EKG sensor may be set.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::on_ekgButton_clicked()
{
    //set button colors. selected tab will be highlighted
    setActiveButtonColor(EKG_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(EKG_CONFIGURE);
}

/**************************************************************
 * FUNCTION: on_imuButton_clicked
 * ------------------------------------------------------------
 * This function gets called when the IMU Button is pressed. It
 * sets the active page to the Configure IMU Sensor page. On
 * this page, different attributes of the IMU sensor may be set.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::on_xcelButton_clicked()
{

    setActiveButtonColor(XCEL_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(XCEL_CONFIGURE);
}

/*Switch from ACC to MAG*/
void maindialog::on_magButton_clicked()
{

    setActiveButtonColor(MAG_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(MAG_CONFIGURE);
}
/**************************************************************
 * FUNCTION: on_gpsButton_clicked
 * ------------------------------------------------------------
 * This function gets called when the GPS Button is pressed. It
 * sets the active page to the Configure GPS Sensor page. On
 * this page, different attributes of the GPS sensor may be set.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::on_gpsButton_clicked()
{
    //set button colors. selected tab will be highlighted
    setActiveButtonColor(GPS_CONFIGURE);

    ui->ConfigurePages->setCurrentIndex(GPS_CONFIGURE);
}

/**************************************************************
 * FUNCTION: setActiveButtonColor
 * ------------------------------------------------------------
 * This function sets the colors of the sensor buttons. The
 * button for the page that is currently active will be
 * highlighted a different color. All of the remaining buttons
 * will be their normal color. This function uses the
 * enumerated page number to determine which button to
 * highlight. All of the other buttons are "set" to their
 * normal colors if any of them were previously highlighted.
 * Upon returning to the configure homepage, all of the buttons
 * are set back to their normal color.
 *
 *  Parameters:
 *      pageToHighlight : Enum value of button to highlight.
 *
 *  Returns: void
 **************************************************************/
void maindialog::setActiveButtonColor(CONFIGURE_PAGES pageToHighlight)
{
    switch(pageToHighlight)
    {
        case GPS_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(241, 181, 33)");
            ui->xcelButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->magButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case XCEL_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->xcelButton->setStyleSheet("background-color:rgb(241, 181, 33)");
            ui->magButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case MAG_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->magButton->setStyleSheet("background-color:rgb(241, 181, 33)");
            ui->xcelButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case EKG_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(241, 181, 33)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->xcelButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->magButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case TEMPERATURE_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->xcelButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->magButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(241, 181, 33)");
        } break;
        case LIGHT_CONFIGURE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->xcelButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->magButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(241, 181, 33)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
        case CONFIGURE_DEV_HOME_PAGE: {
            ui->ekgButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->gpsButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->xcelButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->magButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->lightButton->setStyleSheet("background-color:rgb(152, 162, 173)");
            ui->temperatureButton->setStyleSheet("background-color:rgb(152, 162, 173)");
        } break;
    }
}
