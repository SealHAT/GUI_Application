#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "sensor_header/seal_Types.h"
#include "sensor_header/gps.h"
#include "sensor_header/max30003types.h"
#include "sensor_header/max44009.h"
#include "sensor_header/max44009Types.h"
#include <QDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <list>

namespace Ui {
class maindialog;
}

class maindialog : public QDialog
{
    Q_OBJECT

 /***********************GUI------------->MICROCONTROLLER*****************/
    typedef struct __attribute__((__packed__)){
        uint16_t srtSym;    // symbol to indicate start of packet
        uint16_t id;	    // Upper four bits is the device ID, lower four are device specific event flags
        uint16_t size;		// size of data packet to follow. in bytes or samples? (worst case IMU size in bytes would need a uint16 :( )
    } DATA_HEADER_t;

    struct Xcel_TX{
        DATA_HEADER_t acc_headerData;
        uint32_t acc_activeHour;

        ACC_FULL_SCALE_t acc_scale;
        ACC_OPMODE_t    acc_mode;
        ACC_INT2_type_t acc_dimension;
        uint8_t threshold;
        uint8_t duration;
    };

    struct Mag_TX{
        DATA_HEADER_t mag_headerData;
        uint32_t mag_activeHour;

        MAG_OPMODE_t    mag_mode;
    };

    struct TempLight_TX{
        DATA_HEADER_t templight_headerData;
        uint32_t temp_activeHour;

        uint32_t sample_period = 0;
    };

    struct Ekg_TX{
        DATA_HEADER_t ekg_headerData;
        uint32_t ekg_activeHour;

        uint32_t sample_period = 0;
    };

    enum CONFIGURE_PAGES {
        CONFIGURE_DEV_HOME_PAGE     = 0,
        XCEL_CONFIGURE              = 1,
        MAG_CONFIGURE               = 2,
        GPS_CONFIGURE               = 3,
        EKG_CONFIGURE               = 4,
        TEMPERATURE_CONFIGURE       = 5,
        LIGHT_CONFIGURE             = 6,
    };

    enum DATA_RETRIEVAL_PAGES {
        RETRIEVE_DATA_HOME_PAGE,
        DOWNLOAD_PROGRESS_PAGE,
    };

    enum WELCOME_PAGES {
        INITIAL_PAGE = 0,
    };

    enum IMU_MODE{
        ACC_6D_ENABLE       = 0x80,
        ACC_4D_ENABLE       = 0x00,

        ACC_2G_SCALE        = 0x00,
        ACC_4G_SCALE        = 0x20,
        ACC_8G_SCALE        = 0x40,

        ACC_HR_PWR          = 0x00,
        ACC_NORM_PWR        = 0x08,
        ACC_LP_PWR          = 0x10,

        ACC_1HZ_FREQ        = 0x000,
        ACC_10HZ_FREQ       = 0x001,
        ACC_25HZ_FREQ       = 0x010,
        ACC_50HZ_FREQ       = 0x011,
        ACC_100HZ_FREQ      = 0x100,
        ACC_200HZ_FREQ      = 0x101,
        ACC_400HZ_FREQ      = 0x110,
    };

    enum IMU_PAGES {
    };

    enum ACC_PWR_MODE {
        ACC_LP      = 0,
        ACC_NORMAL  = 1,
        ACC_HR  = 2,
    };

    enum ACC_SCALE {
        ACC_2G = 0,
        ACC_4G = 1,
        ACC_8G = 2,
    };

    enum ACC_FREQUENCY_VALUES {
        ACC_FREQ_1HZ = 0,
        ACC_FREQ_10HZ = 1,
        ACC_FREQ_25HZ = 2,
        ACC_FREQ_50HZ = 3,
        ACC_FREQ_100HZ = 4,
        ACC_FREQ_200HZ = 5,
        ACC_FREQ_400HZ = 6,
    };

    enum MAG_PWR_MODE {
        MAG_LP      = 0,
        MAG_NORMAL  = 1,
    };


    enum MAG_FREQUENCY_VALUES {
        MAG_FREQ_10HZ = 0,
        MAG_FREQ_20HZ = 1,
        MAG_FREQ_50HZ = 2,
        MAG_FREQ_100HZ = 3,
    };

    enum MAG_GAIN_VALUES {
        EKG_20_GAIN = 0,
        EKG_40_GAIN = 1,
        EKG_80_GAIN = 2,
        EKG_160_GAIN = 3,
    };


    enum EKG_LP_FREQUENCY_VALUES {
        EKG_LP_FREQ_BYPASS = 0,
        EKG_LP_FREQ_40HZ = 1,
        EKG_LP_FREQ_100HZ = 2,
        EKG_LP_FREQ_150HZ = 3,
    };


    enum VALIDATOR_STATES {
        INVALID = 0,
        INTERMEDIATE = 1,
        ACCEPTABLE = 2
    };


public:
    explicit maindialog(QWidget *parent = 0);
    void centerDialog();

    ~maindialog();

private slots:

//Button
    void on_backButton_clicked(); //

    void on_configureDevOptionButton_clicked(); //

    void on_retrieveDataButton_clicked(); //

    void on_configureHomeButton_clicked();

    void on_lightButton_clicked();

    void on_temperatureButton_clicked();

    void on_ekgButton_clicked();

    void on_gpsButton_clicked();

    void setActiveButtonColor(CONFIGURE_PAGES pageToHighlight);

    void on_backButton2_clicked();

    void on_magButton_clicked();

    void on_xcelButton_clicked();

//Main_funct_control
    void hour_clicked();

    void labels_hide();

//Accelerometer
    void on_xcel_SW_clicked();

    void xcel_setDefault();

    void IMUxcel_Disable(bool disable);

    void on_xcel_thres_editingFinished();

    void on_xcel_duration_editingFinished();

    void xcel_timeTable_control();

    void xcel_disable_button(bool disable);


//Magnetometer
    void on_mag_SW_clicked();

    void mag_setDefault();

    void IMUmag_Disable(bool disable);

    void mag_disable_button(bool disable);

    void mag_timeTable_control();

//EKG
    void on_ekg_SW_clicked();

    void ekg_setDefault();

    void ekg_Disable(bool disable);

    void ekg_disable_button(bool disable);

    void ekg_timeTable_control();

    //void ekg_LPFreq_CombinationSet();

//GPS
    void on_gps_SW_clicked();

    void gps_disable(bool disable);

    void gps_disable_button(bool disable);

    void gps_timeTable_control();

//Temperature
    void on_temp_SW_clicked();

    void temp_setDefault();

    void temp_disable(bool disable);

    void temp_disable_button(bool disable);

    void temp_timeTable_control();

    void on_temp_freq_editingFinished();




    void on_ekg_odr256_clicked();

    void on_ekg_odr128_clicked();

    void on_ekg_odr512_clicked();

    void on_chooseDestButton_clicked();

    void on_storeData_destinationEdit_editingFinished();

    void on_completeButton_clicked();

//Configuration list
    void setConfigList();

    void on_xcel_timeclear_button_clicked();

private:
    Ui::maindialog *ui;
};

#endif // MAINDIALOG_H
