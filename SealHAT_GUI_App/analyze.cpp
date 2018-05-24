#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

#define EKG_I_AVDV  100/1000000
#define EKG_I_OV    1.6/1000000
#define EKG_I_SAVDV 2.5/1000000
#define EKG_I_SOV   1.1/1000000
#define EKG_OSCILLATOR  (1.4/1000000)*24

uint16_t ekg_sampleNumber;
double ekg_activeHour;
double ekg_activePower;
double ekg_inactivePower;
double ekg_totalPower;

#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(10)

uint16_t temp_sampleNumber;
double temp_activeHour;
double temp_activePower;
double temp_inactivePower;
double temp_totalPower;

uint16_t light_sampleNumber;
double light_activeHour;
double light_activePower;
double light_inactivePower;
double light_totalPower;

uint16_t acc_sampleNumber;
double acc_activeHour;
double acc_activePower;
double acc_inactivePower;
double acc_totalPower;

uint16_t mag_sampleNumber;
double mag_activeHour;
double mag_activePower;
double mag_inactivePower;
double mag_totalPower;

uint16_t gps_sampleNumber;
double gps_activeHour;
double gps_activePower;
double gps_inactivePower;
double gps_totalPower;

uint16_t accFrequency[8] = {1,10,25,50,100,200,400};
double acc_actPower[3][8] = {
                        (3.7/1000000), (5.4/1000000), (8/1000000), (12.6/1000000), (22/1000000), (40/1000000), (75/1000000),
                         (3.7/1000000), (4.4/1000000), (5.6/1000000), (7.7/1000000),(11.7/1000000),(20/1000000),(36/1000000),
                         (3.7/1000000), (5.4/1000000), (8/1000000), (12.6/1000000), (22/1000000), (40/1000000), (75/1000000)};
/*
double accHR_NORM_Power[8] = {3.7/1000000,
                             5.4/1000000,
                             8/1000000,
                             12.6/1000000,
                             22/1000000,
                             40/1000000,
                             75/1000000,};

*/
uint16_t magFrequency[4] = {1,20,50,100};
double magPower[2][4] = {(100/1000000), (200/1000000), (475/1000000), (950/1000000),
                         (25/1000000), (50/1000000), (125/1000000), (250/1000000)};

/*double magNormPower[4] = {25/1000000,
                        50/1000000,
                        125/1000000,
                        250/1000000};*/
uint8_t maindialog::num_Hours(uint32_t x) {
  uint8_t hours =0;
  while(x!=0) {
    x>>=1;
    if(x & 1)
      hours++;
  }
  return hours;
}

void maindialog::powerEstimation(){
   /*TEMPERATURE POWER*/
    temp_sampleNumber = 3600/(configuration_settings.temperature_config.temp_samplePeriod);
    temp_activeHour = num_Hours(configuration_settings.temperature_config.temp_activeHour);
    temp_activePower = ((((3600 - (temp_sampleNumber * TEMP_CONV_TIME)) - (temp_sampleNumber * TEMP_BIT_NUM * I2C_Speed)) * TEMP_SB_PWR)
                        + (temp_sampleNumber * TEMP_CONV_TIME * TEMP_CONV_PWR)
                        + (temp_sampleNumber * TEMP_BIT_NUM * TEMP_I2C_PWR * I2C_Speed)) * temp_activeHour/3600;
    temp_inactivePower = (24 - temp_activeHour) * TEMP_SB_PWR;
    temp_totalPower = (temp_activePower + temp_inactivePower);   //temp power per day//
    //myqDebug() << "temp power is"<< temp_totalPower << endl;

    /*LIGHT POWER*/
     light_sampleNumber = 3600/(configuration_settings.temperature_config.temp_samplePeriod);
     light_activeHour = num_Hours(configuration_settings.temperature_config.temp_activeHour);
     light_activePower = (((3600 - (light_sampleNumber * LIGHT_BIT_NUM * I2C_Speed)) * LIGHT_INACT_PWR/3600)
                        + ((3600 * light_sampleNumber * LIGHT_BIT_NUM * I2C_Speed) * LIGHT_ACT_PWR/3600)) * light_activeHour;
     light_inactivePower = (24 - light_activeHour) * LIGHT_INACT_PWR;
     light_totalPower = light_activePower + light_inactivePower;   //light power per day//
     //qDebug() << "light activehour is" << light_activeHour << endl;
    // myqDebug() << "light inactive power is"<< light_totalPower << endl;

     /*EKG POWER*/
     ekg_sampleNumber = 512/(2<<(configuration_settings.ekg_config.ekg_sampleRate - 1));
     ekg_activeHour = num_Hours(configuration_settings.ekg_config.ekg_activeHour);
     ekg_inactivePower = EKG_I_SAVDV * (24 - ekg_activeHour) + (EKG_I_OV * (24 - ekg_activeHour));
     ekg_activePower = (EKG_I_AVDV + EKG_I_OV) * ekg_activeHour;
     ekg_totalPower = ekg_inactivePower + ekg_activePower + EKG_OSCILLATOR;
     qDebug() << "ekg power is" << ekg_totalPower << endl;

     /*ACCELEROMETER POWER*/
     uint8_t acc_tens = (configuration_settings.accelerometer_config.acc_mode/16)%10 - 1;
     uint8_t acc_pwrMode = (configuration_settings.accelerometer_config.acc_mode%16)%4;

     acc_sampleNumber = 3600/(accFrequency[acc_tens]);
     acc_activeHour = num_Hours(configuration_settings.accelerometer_config.acc_activeHour);
     acc_inactivePower = IMU_SB_PWR * (24 - acc_activeHour);
     acc_activePower = acc_actPower[acc_pwrMode][acc_tens] * acc_activeHour ;//(EKG_I_AVDV + EKG_I_OV) * ekg_activeHour;
     acc_totalPower = acc_inactivePower + acc_activePower;

     /*MAGNETOMETER POWER*/
     uint8_t mag_ones = (configuration_settings.magnetometer_config.mag_mode%16)/4;
     uint8_t mag_powerMode = (configuration_settings.magnetometer_config.mag_mode/16)/10;
     mag_sampleNumber = 3600/(magFrequency[mag_ones]);

     mag_activeHour = num_Hours(configuration_settings.magnetometer_config.mag_activeHour);
     mag_inactivePower = IMU_SB_PWR*(24 - mag_activeHour);
     mag_activePower = magPower[mag_powerMode][mag_ones] * ekg_activeHour;
     mag_totalPower = acc_inactivePower + acc_activePower;
     qDebug() << "mag tens is" << magFrequency[mag_ones];
     qDebug() << "mag accelerometer_sampleNumber is" << mag_sampleNumber << endl;

     /*GPS POWER*/
     gps_sampleNumber = (2*3600)/(30) + (22*3600)/3600;
     gps_activeHour = num_Hours(configuration_settings.gps_config.gps_activeHour);
     gps_inactivePower = GPS_SB_PWR * (24 - gps_activeHour);
     gps_activePower = (77.9/1000000)/30 * gps_activeHour;
     gps_totalPower = gps_inactivePower + gps_activePower;



}

uint64_t templight_storage;
uint64_t acc_storage;
uint64_t mag_storage;
uint64_t gps_storage;
uint64_t ekg_storage;

uint64_t templight_groupNum;
uint64_t acc_groupNum;
uint64_t mag_groupNum;
uint64_t gps_groupNum;
uint64_t ekg_groupNum;

void maindialog::storageEstimation(){
    /*Environment*/
    templight_storage = (4 * configuration_settings.temperature_config.temp_headerData.size + sizeof(DATA_HEADER_t));
    acc_storage = (6 * configuration_settings.accelerometer_config.acc_headerData.size + sizeof(DATA_HEADER_t));
    mag_storage = (6 * configuration_settings.magnetometer_config.mag_headerData.size + sizeof(DATA_HEADER_t));
    gps_storage = (20 * configuration_settings.gps_config.gps_headerData.size + sizeof(DATA_HEADER_t));
    ekg_storage = (3 * configuration_settings.ekg_config.ekg_headerData.size + sizeof(DATA_HEADER_t));

    templight_groupNum = (temp_sampleNumber+light_sampleNumber)/(configuration_settings.temperature_config.temp_headerData.size);
    acc_groupNum = (acc_sampleNumber)/(configuration_settings.accelerometer_config.acc_headerData.size);
    mag_groupNum = (mag_sampleNumber)/(configuration_settings.magnetometer_config.mag_headerData.size);
    gps_groupNum = (gps_sampleNumber)/(configuration_settings.gps_config.gps_headerData.size);
    ekg_groupNum = (ekg_sampleNumber)/(configuration_settings.ekg_config.ekg_headerData.size);

    powerEst = templight_storage * templight_groupNum
             + acc_storage * acc_groupNum
             + mag_storage * mag_groupNum
             + gps_storage * gps_groupNum
             + ekg_storage * ekg_groupNum;
}
