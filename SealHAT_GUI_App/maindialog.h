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

private:
    Ui::maindialog *ui;
};

#endif // MAINDIALOG_H
