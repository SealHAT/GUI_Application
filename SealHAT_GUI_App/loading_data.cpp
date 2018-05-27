#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

/**************************************************************
 * FUNCTION: collectLoadingData_fromFile
 * ------------------------------------------------------------
 * This function gets called file is loaded back from clicking
 * the load button on the Device Configure pages.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::collectLoadingData_fromFile()
{
    configuration_settings.accelerometer_config.acc_activeHour = config[ "Accelerometer Time"];
    configuration_settings.accelerometer_config.acc_scale = (ACC_FULL_SCALE_t)config[ "Accelerometer Scale"];
    configuration_settings.accelerometer_config.acc_mode = (ACC_OPMODE_t)config[ "Accelerometer Mode"];
    configuration_settings.accelerometer_config.acc_sensitivity = config[ "Accelerometer Sensitivity"];
    configuration_settings.accelerometer_config.acc_threshold = config["Accelerometer Threshold"];

    configuration_settings.magnetometer_config.mag_activeHour = config["Magnetometer Time"];
    configuration_settings.magnetometer_config.mag_mode = (MAG_OPMODE_t)config["Magnetometer Mode"];

    configuration_settings.ekg_config.ekg_activeHour = config["EKG Time"];
    configuration_settings.ekg_config.ekg_sampleRate = (CNFGECG_RATE_VAL)config["EKG Sample Rate"];
    configuration_settings.ekg_config.ekg_gain = (CNFGECG_GAIN_VAL)config["EKG Gain"];
    configuration_settings.ekg_config.ekg_lowpassFreq = (CNFGECG_DLPF_VAL)config["EKG Low Pass Frequency"];

    configuration_settings.temperature_config.temp_activeHour = config["Temperature and Light Time"];
    configuration_settings.temperature_config.temp_samplePeriod = config[ "Temperature and Light Sample Period"];

    configuration_settings.gps_config.gps_activeHour = config["GPS Time"];

    loaddata_fromSensors();
    generalEstimation();

}
void maindialog::loaddata_fromSensors(){
    gps_getloadData();
    xcel_getloadData();
    ekg_getloadData();
    mag_getloadData();
    temp_getloadData();

    xcel_checkTimetoEnable();
    ekg_checkTimetoEnable();
    mag_checkTimetoEnable();
    temp_checkTimetoEnable();
}

