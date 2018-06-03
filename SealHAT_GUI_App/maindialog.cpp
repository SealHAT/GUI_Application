#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <QtWidgets>
#include "maindialog.h"
#include "ui_maindialog.h"

/**
 * Initial GUI setup.
 **/
maindialog::maindialog(QWidget *parent) : QDialog(parent), ui(new Ui::maindialog)
{
    ui->setupUi(this);

    // On the Login stack, set the welcome page.
    ui->StartPageStacked->setCurrentIndex(INITIAL_PAGE);

    // Set size for smaller welcome screen.
    this->setFixedSize(350, 350);

    //micro serial stuff
    microSerial_is_available = false;
    //microSerial_port_name = "";

    //hide unused ui coponents for now. TODO: remove unused components
    ui->batterySizeText->hide();
    ui->pwrEst_Text->hide();
    ui->storageEst_Text->hide();
    ui->pwrConsumption_Text->hide();
    ui->storageConsumption_Text->hide();

    //Hide all the warning labels
    labels_hide();
    display_setReadOnly();

    //Set all the sensor configuration back to default
    sensors_setDefault();
    generalEstimation();

    sensors_timeTable_control();
    sensor_esitimation_control();
    configureSettingListDisplay();

    //allocate memory for serial port objects
    microSerial = new QSerialPort(this);

    QObject::connect(microSerial, SIGNAL(readyRead()), this, SLOT(serialReceived()));

    //scan the serial ports and populate combo box on configuration home page
    refreshSerialPorts();

    //initialize current active COM port.
    current_COM_port = ui->comboBox_comPorts->currentText();

    serialInitAndOpenPort();

    //receiveSerial_samples();
    qDebug() << ":)";
}

void maindialog::refreshSerialPorts()
{
    qDebug() << "Num ports available: " << QSerialPortInfo::availablePorts().count() << "\n";

    //clear current entries so they may be updated
    ui->comboBox_comPorts->clear();

    //update the combo box with the currently available COM ports
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->comboBox_comPorts->addItem(serialPortInfo.portName());
        qDebug() << serialPortInfo.portName() << "\n";
    }
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
}

void maindialog::on_configureDevOptionButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(CONFIGURE_MAIN_STACK);
    ui->ConfigurePages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
    setActiveButtonColor(CONFIGURE_DEV_HOME_PAGE);
}


void maindialog::on_retrieveDataButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(RETRIEVE_MAIN_STACK);
    ui->ConfigurePages->setCurrentIndex(RETRIEVE_DATA_HOME_PAGE);
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
}

void maindialog::on_backButton_StreamPage_clicked()
{
    on_backButton_clicked();
}

void maindialog::on_pushButton_refreshCOM_clicked()
{
    refreshSerialPorts();
}

void maindialog::on_comboBox_comPorts_currentIndexChanged(const QString &arg1)
{
    (void)arg1; //unused

    //close port if its currently open
    if(microSerial->isOpen())
    {
        microSerial->close();
    }

    //initialize current active COM port.
    current_COM_port = ui->comboBox_comPorts->currentText();

    //set name of new port and open it
    microSerial->setPortName(current_COM_port);
    serialInitAndOpenPort();

    qDebug() << "Current active port: " << current_COM_port << "\n";
}

void maindialog::serialInitAndOpenPort()
{
    microSerial->open(QSerialPort::ReadWrite);
    microSerial->setBaudRate(QSerialPort::Baud9600);
    microSerial->setDataBits(QSerialPort::Data8);
    microSerial->setParity(QSerialPort::NoParity);
    microSerial->setStopBits(QSerialPort::OneStop);
    microSerial->setFlowControl(QSerialPort::NoFlowControl);
    microSerial->setDataTerminalReady(true);
}

void maindialog::on_sButton_clicked()
{
    //send_serialSetup();
    QByteArray configData;
    configData.append("s");//config_serialize();

    const qint64 bytesWritten = microSerial->write(configData);
    qDebug() << "number of bytes sending" <<bytesWritten << endl;

    if (bytesWritten == -1)
    {
        qDebug() <<"Failed to write the data to port" << endl;
        serial_retry = true;
    } else if (bytesWritten != configData.size()) {
        qDebug() <<"Failed to write all the data to port" << endl;
        serial_retry = true;
    } else if (!microSerial->waitForBytesWritten(5000)) {
        qDebug() <<"Operation timed out or an error "
                   "occurred, error:"<< microSerial->errorString()<< endl;
    }else{
        qDebug() <<"Data successfully sent to port"<< endl;
    }
}

void maindialog::on_oButton_clicked()
{
    //send_serialSetup();
    QByteArray configData;
    configData.append("o");//config_serialize();

    const qint64 bytesWritten = microSerial->write(configData);
    qDebug() << "number of bytes sending" <<bytesWritten << endl;

    if (bytesWritten == -1)
    {
        qDebug() <<"Failed to write the data to port" << endl;
        serial_retry = true;
    } else if (bytesWritten != configData.size()) {
        qDebug() <<"Failed to write all the data to port" << endl;
        serial_retry = true;
    } else if (!microSerial->waitForBytesWritten(5000)) {
        qDebug() <<"Operation timed out or an error "
                   "occurred, error:"<< microSerial->errorString()<< endl;
    }else{
        qDebug() <<"Data successfully sent to port"<< endl;
    }
}
