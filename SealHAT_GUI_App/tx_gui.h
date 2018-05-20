#ifndef TX_GUI_H
#define TX_GUI_H

#include "tx_gui.h"
#include "sensor_header/seal_Types.h"
#include "sensor_header/LSM303AGR.h"
#include "sensor_header/LSM303AGRTypes.h"
#include "sensor_header/gps.h"
#include "sensor_header/max30003types.h"
#include "sensor_header/max44009.h"
#include "sensor_header/max44009Types.h"


/***********************GUI------------->MICROCONTROLLER*****************/
enum SENSOR_OP {
    XCEL_OP              = 1,
    MAG_OP               = 2,
    GPS_OP               = 3,
    EKG_OP               = 4,
    TEMPERATURE_OP       = 5,
    LIGHT_OP             = 6,
};

   typedef struct __attribute__((__packed__)){
       uint16_t srtSym;    // symbol to indicate start of packet
       DEVICE_ID_t id;	    // Upper four bits is the device ID, lower four are device specific event flags
       //uint16_t size;		// size of data packet to follow. in bytes or samples? (worst case IMU size in bytes would need a uint16 :( )
   } DATA_HEADER_t;

   struct Xcel_TX{
       DATA_HEADER_t acc_headerData;

       uint32_t xcel_activeHour;
       ACC_FULL_SCALE_t acc_scale;
       ACC_OPMODE_t    acc_mode;
       uint8_t acc_sensitivity;
       uint8_t threshold;
       uint8_t duration;
   };

   struct Mag_TX{
       DATA_HEADER_t mag_headerData;

       uint32_t mag_activeHour;
       MAG_OPMODE_t    mag_mode;
   };


   struct Temp_TX{
       DATA_HEADER_t temp_headerData;

       uint32_t temp_activeHour;
       uint16_t temp_samplePeriod;
   };

   struct Ekg_TX{
       DATA_HEADER_t ekg_headerData;

       uint32_t ekg_activeHour;
       CNFGECG_RATE_VAL ekg_sampleRate;
       CNFGECG_GAIN_VAL ekg_gain;
       CNFGECG_DLPF_VAL ekg_lpFreq;
   };

   struct GPS_TX{
       DATA_HEADER_t gps_headerData;

       uint32_t gps_activeHour;
   };



#endif // TX_GUI_H
