/*
 * seal_Types.h
 *
 * Created: 15-May-18 22:45:12
 * Author: Ethan
 */

#ifndef SEAL_TYPES_H_
#define SEAL_TYPES_H_

#define SEAL_HAT_VERSION        (1.0)
#define SEALHAT_BASE_YEAR       (2018)

#define PAGE_SIZE_EXTRA         (2176)              /* Maximum NAND Flash page size (*including* extra space) */
#define PAGE_SIZE_LESS          (2048)              /* Maximum NAND Flash page size (*excluding* extra space) */

#define MSG_START_SYM           (0xADDE)

#include "sensor_header/LSM303AGR.h"
#include "sensor_header/LSM303AGRTypes.h"
#include "sensor_header/gps.h"
//#include "sensor_header/ecg.h"
#include "sensor_header/max30003types.h"
#include "sensor_header/max44009.h"
#include "sensor_header/max44009Types.h"

/** Sensor types */
typedef enum {
    DEVICE_ID_RESERVED          = 0x00,
    DEVICE_ID_ENVIRONMENTAL     = 0x10,
    DEVICE_ID_LIGHT             = 0x20,
    DEVICE_ID_TEMPERATURE       = 0x30,
    DEVICE_ID_ACCELEROMETER     = 0x40,
    DEVICE_ID_MAGNETIC_FIELD    = 0x50,
    DEVICE_ID_GYROSCOPE         = 0x60,
    DEVICE_ID_PRESSURE          = 0x70,
    DEVICE_ID_DEPTH             = 0x80,
    DEVICE_ID_GPS               = 0x90,
    DEVICE_ID_EKG               = 0xA0,
    DEVICE_ID_UNUSED            = 0xB0,
    DEVICE_ID_UNUSED1           = 0xC0,
    DEVICE_ID_UNUSED2           = 0xD0,
    DEVICE_ID_SYSTEM            = 0xE0,
    DEVICE_ID_MASK              = 0xF0
} DEVICE_ID_t;

/** Device error codes and flags **/
typedef enum {
    DEVICE_ERR_NONE             = 0x00,
    DEVICE_ERR_COMMUNICATIONS   = 0x01,
    DEVICE_ERR_TIMEOUT          = 0x02,
    DEVICE_ERR_OVERFLOW         = 0x03,
    DEVICE_ERR_CRC              = 0x04,
    DEVICE_ERR_UNK2             = 0x05,
    DEVICE_ERR_UNK3             = 0x06,
    DEVICE_ERR_UNK4             = 0x07,
    DEVICE_ERR_UNK5             = 0x08,
    DEVICE_ERR_UNK6             = 0x09,
    DEVICE_ERR_UNK7             = 0x0A,
    DEVICE_ERR_UNK8             = 0x0B,
    DEVICE_ERR_UNK9             = 0x0C,
    DEVICE_ERR_UNK10            = 0x0D,
    DEVICE_ERR_UNK11            = 0x0E,
    DEVICE_ERR_MASK             = 0x0F
} DEVICE_ERR_CODES_t;

enum SENSOR_OP {
    XCEL_OP              = 1,
    MAG_OP               = 2,
    GPS_OP               = 3,
    EKG_OP               = 4,
    TEMPERATURE_OP       = 5,
    LIGHT_OP             = 6,
};

/** Header for data packets from the device **/
typedef struct __attribute__((__packed__)){
    uint16_t startSym;    // symbol to indicate start of packet
    uint16_t id;	      // Upper four bits is the device ID, lower four are device specific event flags
    uint32_t timestamp;   // timestamp. how many bits?
    uint16_t msTime;      // timestamp ms part
    uint16_t size;		  // size of data packet to follow in bytes
} DATA_HEADER_t;



/**
 * \brief Time struct for calendar
 */
struct calendar_date {
    /*range from 1 to 28/29/30/31*/
    uint8_t day;
    /*range from 1 to 12*/
    uint8_t month;
    /*absolute year>= 1970(such as 2000)*/
    uint16_t year;
};

/***********************GUI------------->MICROCONTROLLER*****************/
struct Xcel_TX {
   DATA_HEADER_t    acc_headerData;
   uint32_t         acc_activeHour;
   ACC_FULL_SCALE_t acc_scale;
   ACC_OPMODE_t     acc_mode;
   uint8_t          acc_sensitivity;
   uint16_t         acc_threshold;
};

struct Mag_TX {
   DATA_HEADER_t    mag_headerData;
   uint32_t         mag_activeHour;
   MAG_OPMODE_t     mag_mode;
};


struct Temp_TX {
   DATA_HEADER_t    temp_headerData;
   uint32_t         temp_activeHour;
   uint16_t         temp_samplePeriod;
};

struct EKG_TX {
   DATA_HEADER_t    ekg_headerData;
   uint32_t         ekg_activeHour;
   CNFGECG_RATE_VAL ekg_sampleRate;
   CNFGECG_GAIN_VAL ekg_gain;
   CNFGECG_DLPF_VAL ekg_lowpassFreq;
};


struct GPS_TX {
   DATA_HEADER_t    gps_headerData;
   uint32_t         gps_activeHour;
   GPS_PROFILE      default_profile;
};

struct SENSOR_CONFIGS {
    DATA_HEADER_t   config_header;        // packet header for all configuration data
    uint8_t         num_flash_chips ;      // number of flash chips installed on device
    calendar_date   start_logging_day;    // day the device should begin data collection
    uint32_t        start_logging_time;   // time the device will start on the day given by start_logging_day
    Xcel_TX         accelerometer_config; // configuration data for the accelerometer
    Mag_TX          magnetometer_config;  // configuration data for the magnetometer
    Temp_TX         temperature_config;   // configuration data for the temperature sensor
    EKG_TX          ekg_config;           // configuration data for the EKG
    GPS_TX          gps_config;           // configuration data for the GPS

};

/** Packet that gets sent over USB to the host computer **/
typedef struct __attribute__((__packed__)){
    uint32_t startSymbol;           // start symbol for the data transmission
    uint8_t  data[PAGE_SIZE_EXTRA]; // one page of data from flash
    uint32_t crc;                   // crc32 of the DATA (not the start symbol) using IEEE CRC32 polynomial
} DATA_TRANSMISSION_t;



#endif /* SEAL_TYPES_H_ */
