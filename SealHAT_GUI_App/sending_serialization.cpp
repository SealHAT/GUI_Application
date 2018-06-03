#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <QtWidgets>
#include <QByteArray>
#include <QDataStream>
#include "maindialog.h"
#include "ui_maindialog.h"

/*Cast sensor configuration structures to QByteArray*/

void maindialog::sendSerial_Config(){
    send_serialSetup();
    QByteArray configData;
    configData = config_serialize();

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

QByteArray maindialog::config_serialize(){
    QByteArray byteArray;

    QDataStream stream(&byteArray, QSerialPort::ReadWrite); //QIODevice:WriteOnly
    stream.setVersion(QDataStream::Qt_4_5);

    stream << 'c';

    return byteArray;
}


void maindialog::on_TX_ReScanButton_clicked()
{
    //ui->TX_serialPort_comboBox->clear();

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
            //ui->TX_serialPort_comboBox->addItem(serialPortInfo.portName());
        }
}

/**************************************************************
 * FUNCTION: send_serialSetup
 * ------------------------------------------------------------
 *  This function checks what serial port users selected
 *  in the TX_serialPort_comboBox. Set serial port to write only.
 *
 *  Parameters: None
 *
 *  Returns: void
 **************************************************************/
void maindialog::send_serialSetup()
{
    microSerial_is_available = false;
    current_COM_port = "";
    serialBuffer = "";

    microSerial = new QSerialPort(this);


    current_COM_port = ui->comboBox_comPorts->currentText();

    if(ui->comboBox_comPorts->count() != 0){
        microSerial_is_available = true;
    }else{
        microSerial_is_available = false;
    }

    if(microSerial_is_available)
    {
        //open and configure the port
        microSerial->setPortName(current_COM_port);
        microSerial->open(QSerialPort::ReadWrite);  //Set serial port to write only
        microSerial->setBaudRate(QSerialPort::Baud9600);
        microSerial->setDataBits(QSerialPort::Data8);
        microSerial->setParity(QSerialPort::NoParity);

        microSerial->setStopBits(QSerialPort::OneStop);
        microSerial->setFlowControl(QSerialPort::NoFlowControl);

        qDebug() << "Found Serial Port:  " << current_COM_port;

    }else{
        QMessageBox::warning(this, "Port error", "Could not find the Microcontroller Serial Port!");
    }

}



QDataStream& operator<<(QDataStream& stream, const DATA_HEADER_t& header) {

    stream << header.startSym
           << header.id
           << (quint32)header.timestamp
           << (quint16)header.msTime
           << (quint16)header.size;

    return stream;
}

QDataStream& operator<<(QDataStream& stream, const Xcel_TX& xcel) {

    stream << xcel.acc_headerData
           << (quint32)xcel.acc_activeHour
           << xcel.acc_scale
           << xcel.acc_mode
           << (quint8)xcel.acc_sensitivity
           << (quint16)xcel.acc_sensitivity;

    return stream;
}

QDataStream& operator<<(QDataStream& stream, const Mag_TX& mag) {

    stream << mag.mag_headerData
           << (quint32)mag.mag_activeHour
           << mag.mag_mode;

    return stream;
}

QDataStream& operator<<(QDataStream& stream, const Temp_TX& temp) {

    stream << temp.temp_headerData
           << (quint32)temp.temp_activeHour
           << (quint32)temp.temp_samplePeriod;

    return stream;
}

/*QDataStream& operator<<(QDataStream& stream, const EKG_TX& ekg) {

    stream << ekg.ekg_headerData
           << (quint32)ekg.ekg_activeHour
           << ekg.ekg_sampleRate
           << ekg.ekg_gain
           << ekg.ekg_lowpassFreq;

    return stream;
}*/

QDataStream& operator<<(QDataStream& stream, const GPS_TX& gps) {

    stream << gps.gps_headerData
           << (quint32)gps.gps_activeHour;
           //<< gps.default_profile;

    return stream;
}

QDataStream& operator<<(QDataStream& stream, const calendar_date& calender) {

    stream << (quint8)calender.day
           << (quint8)calender.month
           << (quint8)calender.year;

    return stream;
}

QDataStream& operator<<(QDataStream& stream, const SENSOR_CONFIGS& configs) {

    stream << configs.config_header
           << (quint8)configs.num_flash_chips
           << configs.start_logging_day
           << (quint32)configs.start_logging_time
           << configs.accelerometer_config
           << configs.magnetometer_config
           << configs.temperature_config
           //<< configs.ekg_config
           << configs.gps_config;

    return stream;
}
