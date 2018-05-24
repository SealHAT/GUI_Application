#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

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

uint16_t ekg_sampleNumber;

uint16_t gps_sampleNumber;

uint16_t accFrequency[8] = {1,10,25,50,100,200,400};
double accLowPower[8] = {3.7/1000000,
                        4.4/1000000,
                        5.6/1000000,
                        7.7/1000000,
                        11.7/1000000,
                        20/1000000,
                        36/1000000,};

double accHR_NORMPower[8] = {3.7/1000000,
                        5.4/1000000,
                        8/1000000,
                        12.6/1000000,
                        22/1000000,
                        40/1000000,
                        75/1000000,};


uint16_t magFrequency[4] = {1,20,50,100};
double magLowPower[4] = {100/1000000,
                        200/1000000,
                        475/1000000,
                        950/1000000};
double magNormPower[4] = {25/1000000,
                        50/1000000,
                        125/1000000,
                        250/1000000};

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
     //qDebug() << "ekg sampleNumber is" << ekg_sampleNumber << endl;

     /*ACCELEROMETER POWER*/
     uint16_t acc_tens = (configuration_settings.accelerometer_config.acc_mode/16)%10 - 1;
     acc_sampleNumber = 3600/(accFrequency[acc_tens]);

     /*MAGNETOMETER POWER*/
     uint16_t mag_ones = (configuration_settings.magnetometer_config.mag_mode%16)/4;
     mag_sampleNumber = 3600/(magFrequency[mag_ones]);

     qDebug() << "mag tens is" << magFrequency[mag_ones];
     qDebug() << "mag accelerometer_sampleNumber is" << mag_sampleNumber << endl;

     /*GPS POWER*/
     gps_sampleNumber = (2*3600)/(30) + (22*3600)/3600;

}

void maindialog::storageEstimation(){
    //storageEst = (4 * + configuration_settings.accelerometer_config.acc_headerData.size)
}
