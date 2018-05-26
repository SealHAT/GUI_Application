#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QMap>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <list>
#include "seal_Types.h"


#define	TOHOUR				3600.0
#define I2C_Speed           1.0/400000
#define SPI_SPEED           1.0/1000000

#define TEMP_CONV_TIME      7.0/1000
#define TEMP_CONV_PWR       90/1000000
#define TEMP_BIT_NUM        16.0
#define TEMP_SB_PWR         0.06/1000000
#define TEMP_I2C_PWR        3.5/1000

#define LIGHT_BIT_NUM       16.0
#define LIGHT_INACT_PWR     0.65/1000000
#define LIGHT_ACT_PWR       0.0000016

#define IMU_SB_PWR          2.0/1000000

#define EKG_I_AVDV          100.0/1000000
#define EKG_I_OV            0.6/1000000
#define EKG_I_SAVDV         0.51/1000000
#define EKG_I_SOV           1.1/1000000
#define EKG_OSCILLATOR      (1.4/1000000)*(24.0)

#define floatDebug() qDebug() << fixed << qSetRealNumberPrecision(10)

#define GPS_SB_PWR  20.0/1000000

#define SPI_CURRENT     20.0/1000
#define SPI_SB_CURRENT  15.0/1000000

#define MICRO_ACT_PWR   32.0/1000000
#define MICRO_SB_PWR    4.6/1000000

namespace Ui {class maindialog;}

class maindialog : public QDialog
{
    Q_OBJECT

    /* Struct containing all sensor and micro configuration data. */
    SENSOR_CONFIGS configuration_settings;
    uint32_t total_sampleNumber;

    uint64_t templight_storage;
    uint64_t acc_storage;
    uint64_t mag_storage;
    uint64_t gps_storage;
    uint64_t ekg_storage;

    double micro_lightActiveTime;
    double micro_tempActiveTime;
    double micro_accActiveTime;
    double micro_magActiveTime;
    double micro_gpsActiveTime;
    double micro_ekgActiveTime;


    uint64_t templight_groupNum;
    uint64_t acc_groupNum;
    uint64_t mag_groupNum;
    uint64_t gps_groupNum;
    uint64_t ekg_groupNum;

    uint32_t temp_sampleNumber;
    double temp_activeHour;
    double temp_activePower;
    double temp_inactivePower;
    double temp_totalPower;

    uint32_t light_sampleNumber;
    double light_activeHour;
    double light_activePower;
    double light_inactivePower;
    double light_totalPower;

    uint8_t acc_tens;
    uint8_t acc_pwrMode;
    uint32_t acc_sampleNumber;
    double acc_activeHour;
    double acc_activePower;
    double acc_inactivePower;
    double acc_totalPower;

    uint8_t mag_ones;
    uint8_t mag_pwrMode;
    uint32_t mag_sampleNumber;
    double mag_activeHour;
    double mag_activePower;
    double mag_inactivePower;
    double mag_totalPower;

    uint32_t ekg_sampleNumber;
    double ekg_activeHour;
    double ekg_activePower;
    double ekg_inactivePower;
    double ekg_totalPower;

    uint32_t gps_sampleNumber;
    double gps_activeHour;
    double gps_activePower;
    double gps_inactivePower;
    double gps_totalPower;

    double memory_totalpower;


    double micro_totalpower;
    double micro_activehour;

    uint16_t accFrequency[7] = {1,10,25,50,100,200,400};
    double acc_actPower[3][7] = {
                                 {(3.7/1000000), (5.4/1000000), (8/1000000), (12.6/1000000), (22.0/1000000), (40.0/1000000), (75.0/1000000)},
                                 {(3.7/1000000), (5.4/1000000), (8.0/1000000), (12.6/1000000), (22.0/1000000), (40.0/1000000), (75.0/1000000)},
                                  {(3.7/1000000), (4.4/1000000), (5.6/1000000), (7.7/1000000),(11.7/1000000),(20.0/1000000),(36.0/1000000)}
                                };

    uint16_t magFrequency[4] = {1,20,50,100};
    double magPower[2][4] = {
                                 {(100.0/1000000), (200.0/1000000), (475.0/1000000), (950.0/1000000)},
                                 {(25.0/1000000), (50.0/1000000), (125.0/1000000), (250.0/1000000)}
                                };

    double powerEst;
    uint32_t storageEst;


    /*************
     * GUI PAGES *
     *************/
    enum MAIN_STACK_PAGES {
        WELCOME_MAIN_STACK      = 0,
        CONFIGURE_MAIN_STACK    = 1,
        RETRIEVE_MAIN_STACK     = 2,
        STREAM_MAIN_STACK       = 3,
    };

    enum WELCOME_PAGES {
        INITIAL_PAGE        = 0,
    };

    enum CONFIGURE_PAGES {
        CONFIGURE_DEV_HOME_PAGE = 0,
        XCEL_CONFIGURE          = 1,
        MAG_CONFIGURE           = 2,
        GPS_CONFIGURE           = 3,
        EKG_CONFIGURE           = 4,
        TEMPERATURE_CONFIGURE   = 5,
        LIGHT_CONFIGURE         = 6,
    };

    enum DATA_RETRIEVAL_PAGES {
        RETRIEVE_DATA_HOME_PAGE = 0,
        DOWNLOAD_PROGRESS_PAGE  = 1,
    };

    enum STREAM_DATA_PAGES {
        STREAM_DATA_HOME_PAGE   = 0,
    };

    enum ACC_PWR_MODE {
        ACC_HR              = 0,
        ACC_NORMAL          = 1,
        ACC_LP              = 2,
    };

    enum ACC_SCALE {
        ACC_2G              = 0,
        ACC_4G              = 1,
        ACC_8G              = 2,
        ACC_16G             = 3,
    };


    enum ACC_FREQUENCY_VALUES {
        ACC_FREQ_1HZ        = 0,
        ACC_FREQ_10HZ       = 1,
        ACC_FREQ_25HZ       = 2,
        ACC_FREQ_50HZ       = 3,
        ACC_FREQ_100HZ      = 4,
        ACC_FREQ_200HZ      = 5,
        ACC_FREQ_400HZ      = 6,
    };

    enum MAG_PWR_MODE {
        MAG_LP              = 0,
        MAG_NORMAL          = 1,
    };

    enum MAG_FREQUENCY_VALUES {
        MAG_FREQ_10HZ       = 0,
        MAG_FREQ_20HZ       = 1,
        MAG_FREQ_50HZ       = 2,
        MAG_FREQ_100HZ      = 3,
    };

    enum MAG_GAIN_VALUES {
        EKG_20_GAIN         = 0,
        EKG_40_GAIN         = 1,
        EKG_80_GAIN         = 2,
        EKG_160_GAIN        = 3,
    };

    enum EKG_LP_FREQUENCY_VALUES {
        EKG_LP_FREQ_BYPASS  = 0,
        EKG_LP_FREQ_40HZ    = 1,
        EKG_LP_FREQ_100HZ   = 2,
        EKG_LP_FREQ_150HZ   = 3,
    };

    enum VALIDATOR_STATES {
        INVALID             = 0,
        INTERMEDIATE        = 1,
        ACCEPTABLE          = 2
    };

public:
    explicit maindialog(QWidget *parent = 0);
    void centerDialog();
    ~maindialog();

private slots:

//Page switch
    void on_backButton_clicked(); //
    void on_configureDevOptionButton_clicked(); //
    void on_retrieveDataButton_clicked(); //
    void on_configureHomeButton_clicked();
    void on_lightButton_clicked();
    void on_temperatureButton_clicked();
    void on_ekgButton_clicked();
    void on_gpsButton_clicked();
    void setActiveButtonColor(CONFIGURE_PAGES pageToHighlight);
    void on_backButton_retrieveData_clicked();
    void on_magButton_clicked();
    void on_xcelButton_clicked();
    void goto_DEV();
    void on_streamDataButton_clicked();
    void on_backButton_StreamPage_clicked();

//Main function control
    void hour_clicked();
    void sensors_setDefault();
    void sensors_timeTable_control();
    void labels_hide();
    void generalEstimation();
    void display_setReadOnly();

//Accelerometer
    void on_xcel_SW_clicked();
    void xcel_setDefault();
    void IMUxcel_Disable(bool disable);
    void on_xcel_thres_editingFinished();
    void xcel_timeTable_control();
    void xcel_disable_button(bool disable);
    void on_xcel_timeclear_button_clicked();
    void xcel_hour_clicked();
    void on_xcel_XL_checkBox_clicked(bool checked);
    void on_xcel_XH_checkBox_clicked(bool checked);
    void on_xcel_YL_checkBox_clicked(bool checked);
    void on_xcel_YH_checkBox_clicked(bool checked);
    void on_xcel_ZL_checkBox_clicked(bool checked);
    void on_xcel_ZH_checkBox_clicked(bool checked);
    void on_xcel_scaleBox_currentIndexChanged(int index);
    void xcel_changeMode();
    void on_xcel_pwrBox_currentIndexChanged();
    void on_xcel_freqBox_currentIndexChanged();
    void xcel_estimation_control();


//Magnetometer
    void on_mag_pwrBox_currentIndexChanged();
    void on_mag_freqBox_currentIndexChanged();
    void mag_dataCollect();
    void on_mag_SW_clicked();
    void mag_setDefault();
    void IMUmag_Disable(bool disable);
    void mag_disable_button(bool disable);
    void mag_timeTable_control();
    void on_mag_timeclear_button_clicked();
    void mag_estimation_control();

//EKG
    void on_ekg_SW_clicked();
    void ekg_setDefault();
    void ekg_Disable(bool disable);
    void ekg_disable_button(bool disable);
    void on_ekg_odr256_clicked();
    void on_ekg_odr128_clicked();
    void on_ekg_odr512_clicked();
    void ekg_timeTable_control();
    void on_ekg_timeclear_button_clicked();
    void ekg_hour_clicked();
    void on_ekg_gainBox_currentIndexChanged(int index);
    void on_ekg_LPfreqBox_currentIndexChanged(int index);
    void ekg_estimation_control();

//GPS
    void gps_dataCollect();
    void gps_setDefault();
    void on_gps_SW_clicked();
    void gps_disable(bool disable);
    void gps_disable_button(bool disable);
    void gps_timeTable_control();
    void on_gps_timeclear_button_clicked();
    void mag_hour_clicked();
    void gps_hour_clicked();

//Temperature
    void on_temp_SW_clicked();
    void temp_setDefault();
    void temp_disable(bool disable);
    void temp_disable_button(bool disable);
    void temp_timeTable_control();
    void on_temp_freq_editingFinished();
    void on_temp_timeclear_button_clicked();
    void temp_hour_clicked();

//Data-Retrival Page
    void on_chooseDestButton_clicked();
    void on_completeButton_clicked();
    void on_storeData_destinationEdit_returnPressed();
    //void saveList();


//Configuration list
    void on_getDataButton_clicked();
    void submitConfig();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void configureSettingListDisplay();
    void collectLoadingData_fromFile();

//Estimation&Analyzation
    uint8_t num_Hours(uint32_t x) ;
    void powerEstimation();
    void storageEstimation();

private:
    Ui::maindialog *ui;
    QMap<QString, uint32_t> config;
};

#endif // MAINDIALOG_H
