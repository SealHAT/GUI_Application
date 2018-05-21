#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <list>
#include "seal_Types.h"

namespace Ui {class maindialog;}

class maindialog : public QDialog
{
    Q_OBJECT

    /* Struct containing all sensor and micro configuration data. */
    SENSOR_CONFIGS configuration_settings;

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

    /****************
     * SENSOR ENUMS *
     ****************/
    enum IMU_MODE {
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
        ACC_LP              = 0,
        ACC_NORMAL          = 1,
        ACC_HR              = 2,
    };

    enum ACC_SCALE {
        ACC_2G              = 0,
        ACC_4G              = 1,
        ACC_8G              = 2,
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
    //void hour_clicked_timeConfig(DEVICE_ID_t id);
    void labels_hide();

//Accelerometer
    void on_xcel_SW_clicked();
    void xcel_setDefault();
    void IMUxcel_Disable(bool disable);
    void on_xcel_thres_editingFinished();
    void on_xcel_duration_editingFinished();
    void xcel_timeTable_control();
    void xcel_disable_button(bool disable);
    void on_xcel_timeclear_button_clicked();
    void xcel_hour_clicked();

//Magnetometer
    void mag_dataCollection(Mag_TX *mag);
    void on_mag_SW_clicked();
    void mag_setDefault();
    void IMUmag_Disable(bool disable);
    void mag_disable_button(bool disable);
    void mag_timeTable_control();
    void on_mag_timeclear_button_clicked();

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

//GPS
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
    void on_storeData_destinationEdit_editingFinished();
    void on_completeButton_clicked();

//Configuration list
    void setConfigList();
    void on_mag_pwrBox_currentIndexChanged(int index);

private:
    Ui::maindialog *ui;
};

#endif // MAINDIALOG_H
