#ifndef MAINDIALOG_H
#define MAINDIALOG_H

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

    struct Xcel{
        uint32_t time;
        //uint8_t dimension;
        //uint8_t scale;
        // uint8_t power;

        uint8_t mode; //  6D/4D [7]/scale[6:5]/power[4:3]/sampling rate[2:0]
        uint8_t threshold;
        uint8_t duration;
    };

    struct Temp{
        uint32_t time = 0;
        uint8_t mode = 0;

    };

    Temp finalTemp;
    Temp temporaryTemp;

    struct Ekg{
        bool disable = false;
        uint32_t time = 0;
        uint8_t mode = 0;
    };
    Ekg temporaryEkg;

    enum CONFIGURE_PAGES {
        CONFIGURE_DEV_HOME_PAGE     = 0,
        GPS_CONFIGURE               = 1,
        IMU_CONFIGURE               = 2,
        EKG_CONFIGURE               = 3,
        TEMPERATURE_CONFIGURE       = 4,
        LIGHT_CONFIGURE             = 5,
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
        XCEL_CONFIGURE              = 0,
        MAG_CONFIGURE               = 1,
    };

    enum PWR_MODE {
        ACC_HR      = 0,
        ACC_NORMAL  = 1,
        ACC_LP  = 2,
    };

    enum XCEL_SCALE {
        ACC_2G = 0,
        ACC_4G = 1,
        ACC_8G = 2,
    };

    enum XCEL_FREQUENCY_VALUES {
        FREQ_1HZ = 0,
        FREQ_10HZ = 1,
        FREQ_25HZ = 2,
        FREQ_50HZ = 3,
        FREQ_100HZ = 4,
        FREQ_200HZ = 5,
        FREQ_400HZ = 6,
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
    void on_backButton_clicked(); //

    //void on_adminSignOutButton_clicked(); //

    void on_configureDevOptionButton_clicked(); //

    void on_retrieveDataButton_clicked(); //

    void on_configureHomeButton_clicked();

    void on_lightButton_clicked();

    void on_temperatureButton_clicked();

    void on_ekgButton_clicked();

    void on_imuButton_clicked();

    void on_gpsButton_clicked();

    void setActiveButtonColor(CONFIGURE_PAGES pageToHighlight);

    void on_backButton2_clicked();

    void on_xcel_thres_editingFinished();

    void on_xcel_duration_editingFinished();

    void on_Xcel_swPAGE_clicked();

    void on_Mag_swPAGE_clicked();

    void on_IMU_SW_clicked();

    void IMUxcel_Disable();

    void IMUmag_Disable();

    void IMUxcel_Enable();

    void IMUmag_Enable();

    void on_xcel_SW_clicked();

    void on_mag_SW_clicked();

    void on_xcel_finishButton_clicked();

    void on_mag_finishButton_clicked();

    void hour_clicked();

    void labels_hide();

    void ekg_Disable(bool disable);

    void ekg_disable_button(bool disable);

    void ekg_timeTable_control();

    void on_ekg_SW_clicked();

    void on_gps_SW_clicked();

    void gps_disable(bool disable);

    void gps_disable_button(bool disable);

    void gps_timeTable_control();

    void on_temp_SW_clicked();

    void temp_disable(bool disable);

    void temp_disable_button(bool disable);

    void temp_timeTable_control();

private:
    Ui::maindialog *ui;
};

#endif // MAINDIALOG_H
