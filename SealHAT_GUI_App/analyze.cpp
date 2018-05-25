#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDebug>
#include <QPalette>
#include "maindialog.h"
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
    ekg_sampleNumber = ekg_activeHour*3600*(512/(2<<(configuration_settings.ekg_config.ekg_sampleRate - 1)));

    acc_tens = (configuration_settings.accelerometer_config.acc_mode/16)%10 - 1; //logic Rethink
    acc_pwrMode = (configuration_settings.accelerometer_config.acc_mode%16)/4;
    acc_activeHour = num_Hours(configuration_settings.accelerometer_config.acc_activeHour);
    acc_sampleNumber = acc_activeHour*(3600)*(accFrequency[acc_tens]);
    qDebug() << "acc_tens is" << acc_tens << endl;
    qDebug() << "acc_pwrMode is" << acc_pwrMode << endl;

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
    //HOUR Bug
   /*TEMPERATURE POWER*/

    //temp_activeHour = num_Hours(configuration_settings.temperature_config.temp_activeHour);
    //temp_sampleNumber = temp_activeHour*3600/(configuration_settings.temperature_config.temp_samplePeriod);
    temp_activePower = ((((3600 - (temp_sampleNumber * TEMP_CONV_TIME)) - (temp_sampleNumber * TEMP_BIT_NUM * I2C_Speed)) * TEMP_SB_PWR)
                        + (temp_sampleNumber * TEMP_CONV_TIME * TEMP_CONV_PWR)
                        + (temp_sampleNumber * TEMP_BIT_NUM * TEMP_I2C_PWR * I2C_Speed)) * temp_activeHour/3600;
    temp_inactivePower = (24 - temp_activeHour) * TEMP_SB_PWR;
    temp_totalPower = (temp_activePower + temp_inactivePower);   //temp power per day//
    //qDebug() << "configuration_settings.temperature_config.temp_activeHour is" << configuration_settings.temperature_config.temp_activeHour << endl;
    //qDebug() << "temp_activePower is" << temp_activePower << endl;
    //qDebug() << "temp_sampleNumber is" << temp_sampleNumber << endl;

    /*LIGHT POWER*/
     //light_activeHour = num_Hours(configuration_settings.temperature_config.temp_activeHour);
     //light_sampleNumber = light_activeHour*3600/(configuration_settings.temperature_config.temp_samplePeriod);
     light_activePower = (((3600 - (light_sampleNumber * LIGHT_BIT_NUM * I2C_Speed)) * LIGHT_INACT_PWR)
                        + (( light_sampleNumber * LIGHT_BIT_NUM * I2C_Speed) * LIGHT_ACT_PWR)) * light_activeHour/3600;
     light_inactivePower = (24 - light_activeHour) * LIGHT_INACT_PWR;
     light_totalPower = light_activePower + light_inactivePower;   //light power per day//
     //qDebug() << "configuration_settings.temperature_config.temp_activeHour is" << configuration_settings.temperature_config.temp_activeHour << endl;
     //qDebug() << "light_activePower is" << light_activePower << endl;
     //qDebug() << "light_sampleNumber is" << light_sampleNumber << endl;
     //qDebug() << "light inactive power is"<< light_totalPower << endl;

     /*EKG POWER*/
     //ekg_activeHour = num_Hours(configuration_settings.ekg_config.ekg_activeHour);
     //ekg_sampleNumber = ekg_activeHour*3600*(512/(2<<(configuration_settings.ekg_config.ekg_sampleRate - 1)));
     ekg_inactivePower = EKG_I_SAVDV * (24 - ekg_activeHour) + (EKG_I_OV * (24 - ekg_activeHour));
     ekg_activePower = (EKG_I_AVDV + EKG_I_OV) * ekg_activeHour;
     ekg_totalPower = ekg_inactivePower + ekg_activePower + EKG_OSCILLATOR;
     //qDebug() << "ekg_activeHour is" << ekg_activeHour << endl;
     //qDebug() << "ekg_sampleNumber is" << ekg_sampleNumber << endl;
     //qDebug() << "ekg_totalPower is" << ekg_totalPower << endl;

     /*ACCELEROMETER POWER*/
     //uint8_t acc_tens = (configuration_settings.accelerometer_config.acc_mode/16)%10 - 1;
     //uint8_t acc_pwrMode = (configuration_settings.accelerometer_config.acc_mode%16)%4;
     //acc_activeHour = num_Hours(configuration_settings.accelerometer_config.acc_activeHour);
     //acc_sampleNumber = acc_activeHour*(3600)*(accFrequency[acc_tens]);
     acc_inactivePower = IMU_SB_PWR * (24 - acc_activeHour);
     acc_activePower = acc_actPower[acc_pwrMode][acc_tens] * acc_activeHour ;//(EKG_I_AVDV + EKG_I_OV) * ekg_activeHour;
     acc_totalPower = acc_inactivePower + acc_activePower;
     qDebug() << "acc_totalPower is" << acc_totalPower << endl;
     qDebug() << "acc_sampleNumber is" << acc_sampleNumber << endl;
     //qDebug() << "acc_activeHour is" << acc_activeHour << endl;
     qDebug() << "accFrequency[acc_tens] is" << accFrequency[acc_tens] << endl;
     //qDebug() << "acc_sampleNumber is" << acc_sampleNumber << endl;

     /*MAGNETOMETER POWER*/
     //uint8_t mag_ones = (configuration_settings.magnetometer_config.mag_mode%16)/4;
     //uint8_t mag_pwrMode = (configuration_settings.magnetometer_config.mag_mode/16)%10;


     //mag_activeHour = num_Hours(configuration_settings.magnetometer_config.mag_activeHour);
     //mag_sampleNumber = mag_activeHour*3600*(magFrequency[mag_ones]);
     mag_inactivePower = IMU_SB_PWR*(24 - mag_activeHour);
     mag_activePower = magPower[mag_pwrMode][mag_ones] * mag_activeHour;
     mag_totalPower = mag_inactivePower + mag_activePower;
     //qDebug() << "mag_sampleNumber is" << mag_sampleNumber << endl;
     //qDebug() << "mag_activePower is" << mag_activePower << endl;

     /*GPS POWER*/

     //gps_activeHour = num_Hours(configuration_settings.gps_config.gps_activeHour);
     //gps_sampleNumber = gps_activeHour*((2*3600)/(30) + (22*3600)/3600);
     gps_inactivePower = GPS_SB_PWR * (24 - gps_activeHour);
     gps_activePower = (77.9/1000000)/30 * gps_activeHour;
     gps_totalPower = gps_inactivePower + gps_activePower;
     //floatDebug() << "gps_totalPower is" << gps_totalPower << endl;

     /*MEMORY POWER*/  //what is the correct SPI time
     memory_totalpower = storageEst * SPI_SPEED/3600 * SPI_CURRENT
                         + (24 - (storageEst * SPI_SPEED)/3600) * SPI_SB_CURRENT
                         + (24 * SPI_SB_CURRENT * 3);
     //qDebug() << "memory_totalpower is" << memory_totalpower << endl;


     /*MICRO POWER*/
     //micro_activehour //How to caculate activehour for micro

     /*Light Temperature I2C + SPI*/
     micro_tempActiveTime = temp_sampleNumber * 2 * (I2C_Speed + SPI_SPEED);
     micro_lightActiveTime = light_sampleNumber * 2 * (I2C_Speed + SPI_SPEED);
     micro_accActiveTime = acc_sampleNumber * 6 * (I2C_Speed + SPI_SPEED);
     micro_magActiveTime = mag_sampleNumber * 6 * (I2C_Speed + SPI_SPEED);
     micro_gpsActiveTime = (gps_sampleNumber * 100 * I2C_Speed) + (gps_sampleNumber * 20 * SPI_SPEED);
     micro_ekgActiveTime = ekg_sampleNumber * 3 * (I2C_Speed + SPI_SPEED);

     micro_activehour = (micro_tempActiveTime + micro_lightActiveTime + micro_accActiveTime + micro_magActiveTime
                      + micro_gpsActiveTime + micro_ekgActiveTime)*8/3600;
     micro_totalpower = micro_activehour * MICRO_ACT_PWR * (12) + ((24-micro_activehour) * MICRO_SB_PWR);

   // qDebug() << "micro_tempActiveTime is" << micro_tempActiveTime << endl;
    //qDebug() << "micro_activehour is" << micro_activehour << endl;
   // qDebug() << "micro_totalpower is" << micro_totalpower << endl;


     powerEst = (temp_totalPower + light_totalPower + ekg_totalPower + acc_totalPower + mag_totalPower + gps_totalPower
                 + memory_totalpower + micro_totalpower) * 1000;
     //qDebug() << "powerEst is" << powerEst << endl;
     ui->pwrEst_Text->setText((QString::number(powerEst,'f',5)));
}




/*Storage caculate in bits = total Bits*/
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

    storageEst = (templight_storage * templight_groupNum
             + acc_storage * acc_groupNum
             + mag_storage * mag_groupNum
             + gps_storage * gps_groupNum
             + ekg_storage * ekg_groupNum) * 8;
    //qDebug() << "templight_storage is" << templight_storage << endl;
    //qDebug() << "temp_sampleNumber is" << temp_sampleNumber << endl;
    //qDebug() << "configuration_settings.temperature_config.temp_headerData.size is" << configuration_settings.temperature_config.temp_headerData.size << endl;
    //qDebug() << "templight_groupNum is" << templight_groupNum << endl;
   // qDebug() << "configuration_settings.ekg_config.ekg_headerData.size is" << configuration_settings.ekg_config.ekg_headerData.size << endl;


    //floatDebug() << "storageEst is" << storageEst << endl;
    ui->storageEst_Text->setText(QString::number(storageEst));
}
