#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDebug>
#include <QPalette>
#include <cmath>
#include "maindialog.h"
#include "analyze.h"
#include "ui_maindialog.h"

uint8_t maindialog::num_Hours(uint32_t x) {
  uint8_t hours =0;
  while(x!=0) {
    x = x & (x-1);
     hours++;
  }
  return hours;
}

/*Combination of power and storage calcualtion and display*/
void maindialog::generalEstimation(){

    temp_activeHour = num_Hours(configuration_settings.temperature_config.temp_activeHour);
    temp_sampleNumber = temp_activeHour*3600/(configuration_settings.temperature_config.temp_samplePeriod);

    light_activeHour = num_Hours(configuration_settings.temperature_config.temp_activeHour);
    light_sampleNumber = light_activeHour*3600/(configuration_settings.temperature_config.temp_samplePeriod);

    ekg_activeHour = num_Hours(configuration_settings.ekg_config.ekg_activeHour);
    uint32_t ekg_spsmode = (512/(pow(2,(uint8_t)configuration_settings.ekg_config.ekg_sampleRate)));
    ekg_sampleNumber = ekg_activeHour*3600*(512/(pow(2,(uint8_t)configuration_settings.ekg_config.ekg_sampleRate)));

    acc_tens = (configuration_settings.accelerometer_config.acc_mode/16)%10 - 1; //logic Rethink
    acc_pwrMode = (configuration_settings.accelerometer_config.acc_mode%16)/4;
    acc_activeHour = num_Hours(configuration_settings.accelerometer_config.acc_activeHour);
    acc_sampleNumber = acc_activeHour*(3600)*(accFrequency[acc_tens]);

    mag_ones = (configuration_settings.magnetometer_config.mag_mode%16)/4;
    mag_pwrMode = (configuration_settings.magnetometer_config.mag_mode/16)%10;
    mag_activeHour = num_Hours(configuration_settings.magnetometer_config.mag_activeHour);
    mag_sampleNumber = mag_activeHour*3600*(magFrequency[mag_ones]);

    gps_activeHour = num_Hours(configuration_settings.gps_config.gps_activeHour);
    gps_sampleNumber = gps_activeHour*((2*3600)/(30) + (22*3600)/3600);

    storageEstimation();
    powerEstimation();
}
/*Power estimation base on changing configuation setting*/
void maindialog::powerEstimation(){
   /*TEMPERATURE POWER*/
    temp_activePower = ((((3600 - (temp_sampleNumber * TEMP_CONV_TIME)) - (temp_sampleNumber * TEMP_BIT_NUM * I2C_Speed)) * TEMP_SB_PWR)
                        + (temp_sampleNumber * TEMP_CONV_TIME * TEMP_CONV_PWR)
                        + (temp_sampleNumber * TEMP_BIT_NUM * TEMP_I2C_PWR * I2C_Speed)) * temp_activeHour/3600;
    temp_inactivePower = (24 - temp_activeHour) * TEMP_SB_PWR;
    temp_totalPower = (temp_activePower + temp_inactivePower);   //temp power per day//

    /*LIGHT POWER*/
     light_activePower = (((3600 - (light_sampleNumber * LIGHT_BIT_NUM * I2C_Speed)) * LIGHT_INACT_PWR)
                        + (( light_sampleNumber * LIGHT_BIT_NUM * I2C_Speed) * LIGHT_ACT_PWR)) * light_activeHour/3600;
     light_inactivePower = (24 - light_activeHour) * LIGHT_INACT_PWR;
     light_totalPower = light_activePower + light_inactivePower;   //light power per day//

     /*EKG POWER*/
     ekg_inactivePower = EKG_I_SAVDV * (24 - ekg_activeHour) + (EKG_I_OV * (24 - ekg_activeHour));
     ekg_activePower = (EKG_I_AVDV + EKG_I_OV) * ekg_activeHour;
     ekg_totalPower = ekg_inactivePower + ekg_activePower + EKG_OSCILLATOR;

     /*ACCELEROMETER POWER*/
     acc_inactivePower = IMU_SB_PWR * (24 - acc_activeHour);
     acc_activePower = acc_actPower[acc_pwrMode][acc_tens] * acc_activeHour ;//(EKG_I_AVDV + EKG_I_OV) * ekg_activeHour;
     acc_totalPower = acc_inactivePower + acc_activePower;

     /*MAGNETOMETER POWER*/
     mag_inactivePower = IMU_SB_PWR*(24 - mag_activeHour);
     mag_activePower = magPower[mag_pwrMode][mag_ones] * mag_activeHour;
     mag_totalPower = mag_inactivePower + mag_activePower;

     /*GPS POWER*/
     gps_inactivePower = GPS_SB_PWR * (24 - gps_activeHour);
     gps_activePower = (77.9/1000000)/30 * gps_activeHour;
     gps_totalPower = gps_inactivePower + gps_activePower;

     /*MEMORY POWER*/  //what is the correct SPI time
     memory_totalpower = storageEst * SPI_SPEED/3600 * SPI_CURRENT
                         + (24 - (storageEst * SPI_SPEED)/3600) * SPI_SB_CURRENT
                         + (24 * SPI_SB_CURRENT * 3);

     /*MICRO POWER*/
     micro_tempActiveTime = temp_sampleNumber * 2 * (I2C_Speed + SPI_SPEED);
     micro_lightActiveTime = light_sampleNumber * 2 * (I2C_Speed + SPI_SPEED);
     micro_accActiveTime = acc_sampleNumber * 6 * (I2C_Speed + SPI_SPEED);
     micro_magActiveTime = mag_sampleNumber * 6 * (I2C_Speed + SPI_SPEED);
     micro_gpsActiveTime = (gps_sampleNumber * 100 * I2C_Speed) + (gps_sampleNumber * 20 * SPI_SPEED);
     micro_ekgActiveTime = ekg_sampleNumber * 3 * (I2C_Speed + SPI_SPEED);

     micro_activehour = (micro_tempActiveTime + micro_lightActiveTime + micro_accActiveTime + micro_magActiveTime
                      + micro_gpsActiveTime + micro_ekgActiveTime)*8/3600;
     micro_totalpower = micro_activehour * MICRO_ACT_PWR * (12) + ((24-micro_activehour) * MICRO_SB_PWR);

//SUM OF POWER
     powerEst = (temp_totalPower + light_totalPower + ekg_totalPower + acc_totalPower + mag_totalPower + gps_totalPower
                 + memory_totalpower + micro_totalpower) * 1000;
     QString powerEstString = (QString::number(powerEst,'f',5));

     double batterySize = ui->batterySizeText->text().toDouble();
     double powerConsumptionValue = powerEst/(double)batterySize;
     QString powerconsumpString = (QString::number(powerConsumptionValue,'f',2)) + " % ";

     if(!(ui->batterySizeText->text().isEmpty()))
     {
         ui->pwrEst_Text->setText(powerEstString + "     " + powerconsumpString);
     }else{
         ui->pwrEst_Text->setText(powerEstString);
     }

}

void maindialog::on_batterySizeText_editingFinished()
{
    QString powerEstString = (QString::number(powerEst,'f',5));
    double batterySize = ui->batterySizeText->text().toDouble();
    uint16_t timeDuration = batterySize/(powerEst);
    uint16_t monthConsump = timeDuration/30;
    uint16_t dayConsump = timeDuration%30;

    QString powerconsumpString = (QString::number(monthConsump)) + " Months "
                                + (QString::number(dayConsump)) + " Days ";

    if(!(ui->batterySizeText->text().isEmpty()))
    {
        ui->pwrEst_Text->setText(powerEstString + "\n" + powerconsumpString);
    }else{
        ui->pwrEst_Text->setText(powerEstString);
    }
}



/*Storage caculate in bits = total Bits*/
void maindialog::storageEstimation(){
    /*Environment*/
    templight_storage = (4 * LIGHT_TEMP_SIZE + sizeof(DATA_HEADER_t));
    acc_storage = (6 * IMU_DATA_SIZE + sizeof(DATA_HEADER_t));
    mag_storage = (6 * IMU_DATA_SIZE + sizeof(DATA_HEADER_t));
    gps_storage = (20 * GPS_DATA_SIZE + sizeof(DATA_HEADER_t));
    ekg_storage = (3 * EKG_DATA_SIZE + sizeof(DATA_HEADER_t));

    templight_groupNum = (temp_sampleNumber+light_sampleNumber)/LIGHT_TEMP_SIZE;
    acc_groupNum = (acc_sampleNumber)/IMU_DATA_SIZE;
    mag_groupNum = (mag_sampleNumber)/IMU_DATA_SIZE;
    gps_groupNum = (gps_sampleNumber)/GPS_DATA_SIZE;
    ekg_groupNum = (ekg_sampleNumber)/EKG_DATA_SIZE;

    storageEst = (templight_storage * templight_groupNum
             + acc_storage * acc_groupNum
             + mag_storage * mag_groupNum
             + gps_storage * gps_groupNum
             + ekg_storage * ekg_groupNum) * 8;

    double StorageConsump = (storageEst)/STORAGECAPACITY;
    QString storageconsumpString = "   " + QString::number(StorageConsump,'f',2) + " % ";
    //ui->storageEst_Text->clear();
    ui->storageEst_Text->setText(QString::number(storageEst) + storageconsumpString);

}
