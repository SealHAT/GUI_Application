#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>

QSerialPort serial;
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
    //Hide all the warning labels
    labels_hide();

    //Set all the sensor configuration back to default
    sensors_setDefault();
    generalEstimation();

    sensors_timeTable_control();
    sensor_esitimation_control();


    display_setReadOnly();
    configureSettingListDisplay();
    //serial = new QSerialPort(this);

    serial.open(QIODevice::ReadWrite);
    serial.setPortName("COM8");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);

    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    serial.open(QIODevice::ReadWrite);
    serial.write("Hello World");
/*
    serial = new QSerialPort(this);
    serial.setPortName("COM4");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);

    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    serial.open(QIODevice::ReadWrite);
    QString writeData = "ok*";
    qint64 bytesWritten;
    serial.write("ok*");

    if (bytesWritten == -1) {
            qDebug() << "Failed to write the data to port, error: " << endl;
        } else if (bytesWritten != writeData.size()) {
            qDebug() << "Failed to write all the data to port , error: " << endl;
        } else if (!serial.waitForBytesWritten(5000)) {
            qDebug() << "Operation timed out or an error ,occurred for port %1, error: %2" << endl;
        }
        connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceived()));
        qDebug() << "Data successfully sent to port %1" << endl;
*/
}


void maindialog::serialReceived()
{
    QByteArray ba;
    ba = serial.readAll();
    ui->serialLabel->setText(ba);
    qDebug() << ba;
}

/*
 * Set all the sensors to default configuration
 * and default display
*/
void maindialog::sensors_setDefault()
{
    xcel_setDefault();
    mag_setDefault();
    ekg_setDefault();
    temp_setDefault();
    gps_setDefault();
}

void maindialog::sensor_esitimation_control(){
    ekg_estimation_control();
    xcel_estimation_control();
    mag_estimation_control();
    gps_estimation_control();
}

/**/
void maindialog::display_setReadOnly()
{
    ui->gps_highSamplingRateValue->setReadOnly(true);
    ui->gps_lowSamplingRateValue->setReadOnly(true);
    ui->pwrEst_Text->setReadOnly(true);
    ui->pwrConsumption_Text->setReadOnly(true);
    ui->storageEst_Text->setReadOnly(true);
    ui->storageConsumption_Text->setReadOnly(true);
    ui->gps_configList->setReadOnly(true);
    ui->xcel_configList->setReadOnly(true);
    ui->mag_configList->setReadOnly(true);
}

/*Set all the sensors to default configuration*/
void maindialog::sensors_timeTable_control()
{
    temp_timeTable_control();
    ekg_timeTable_control();
    gps_timeTable_control();
    xcel_timeTable_control();
    mag_timeTable_control();
}


/* Hide all the warning label*/
void maindialog::labels_hide()
{
    ui->thres_warnLABEL->hide();
    ui->temp_warnLABEL->hide();
}

/**
 * Delete GUI on exit.
 **/
maindialog::~maindialog()
{
    delete ui;
    serial.close();
}

void maindialog::on_configureDevOptionButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(CONFIGURE_MAIN_STACK);
    ui->ConfigurePages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
    setActiveButtonColor(CONFIGURE_DEV_HOME_PAGE);
    this->centerDialog();
}


void maindialog::on_retrieveDataButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(RETRIEVE_MAIN_STACK);
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


void maindialog::on_streamDataButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(STREAM_MAIN_STACK);
    ui->ConfigurePages->setCurrentIndex(STREAM_DATA_HOME_PAGE);
    this->centerDialog();
}

void maindialog::on_backButton_StreamPage_clicked()
{
    on_backButton_clicked();
}



