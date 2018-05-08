#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>

#include <QDebug>

/**
 * Initial GUI setup.
 **/
maindialog::maindialog(QWidget *parent) : QDialog(parent), ui(new Ui::maindialog)
{
    ui->setupUi(this);

    // On the Login stack, set the welcome page.
    ui->StartPageStacked->setCurrentIndex(INITIAL_PAGE);

    // Set size for smaller welcome screen.
    this->setFixedSize(421, 421);

    // Hide all the warning label on the IMU page
    labels_hide();

    ui->PwrStorageText->setReadOnly(true);
    temp_timeTable_control();
    ekg_timeTable_control();
    gps_timeTable_control();
    xcel_timeTable_control();
    mag_timeTable_control();
}

void maindialog::labels_hide()
{
    ui->thres_warnLABEL->hide();
    ui->dur_warnLABEL->hide();
    ui->temp_warnLABEL->hide();
}

/**
 * Delete GUI on exit.
 **/
maindialog::~maindialog()
{
    delete ui;
}

void maindialog::on_configureDevOptionButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(1);
    ui->ConfigurePages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
    this->centerDialog();
}

void maindialog::on_retrieveDataButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(2);
    ui->ConfigurePages->setCurrentIndex(RETRIEVE_DATA_HOME_PAGE);
    this->centerDialog();
}

/**
 * Center the contents of the page.
 **/
void maindialog::centerDialog() {
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}

void maindialog::hour_clicked()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!button->property("clicked").isValid()) {
        button->setProperty("clicked", false);
    }
    bool clicked = button->property("clicked").toBool();
    qDebug() << "1. click before setproperty is :" << clicked << endl;
    button->setProperty("clicked", !clicked);
    qDebug() << "2. click after setproperty is :" << clicked << endl;
    //qDebug() << "time is :" << temporaryTemp.time << endl;
        if(!clicked) {
            button->setStyleSheet("background-color:rgb(34,139,34)");
            //temporaryTemp.time |= 1 << button->property("button_shift").toInt();
            //temporaryEkg.time |= 1 << button->property("button_shift").toInt();
        } else {
            button->setStyleSheet("background-color:rgb(152, 162, 173)");
            //temporaryTemp.time &= ~(1 << button->property("button_shift").toInt());
            //temporaryEkg.time &= ~(1 << button->property("button_shift").toInt());
        }
    //qDebug() << "time is :" << temporaryTemp.time << endl;
    //qDebug() << "time is :" << temporaryEkg.time << endl;
}











