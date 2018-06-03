#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QList>
#include <QMessageBox>
#include <QDataStream>
#include "maindialog.h"
#include "ui_maindialog.h"


void maindialog::receiveSerial_samples()
{
    receive_serialSetup();
    QObject::connect(microSerial, SIGNAL(readyRead()), this, SLOT(serialReceived()));
}

void maindialog::serialReceived()
{
    serial_readData = microSerial->readAll();
    data_deserialize(serial_readData);

    serialBuffer = QString::fromStdString(serial_readData.toStdString());
    ui->serialLabel->setText(serial_readData);
    //qDebug() << serialBuffer;
    qDebug() << "Serial is working";
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
void maindialog::receive_serialSetup()
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
        microSerial->open(QSerialPort::ReadOnly);  //Set serial port to ReadOnly
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

void maindialog::on_RXstream_ReScanButton_clicked()
{
    //ui->RXstream_serialPort_comboBox->clear();

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
           // ui->RXstream_serialPort_comboBox->addItem(serialPortInfo.portName());

        }
}

QDataStream& operator>>(QDataStream& stream, DATA_TRANSMISSION_t& txData) {

    quint32 temp_startSymbol;
    quint32 temp_crc;

    stream >>  temp_startSymbol;

    for(int i=0;i<PAGE_SIZE_EXTRA; i++){
        stream >> txData.data[i];
    }

    stream >> temp_crc;

    txData.startSymbol = temp_startSymbol;
    txData.crc = temp_crc;

    return stream;
}


void maindialog::data_deserialize(QByteArray& byteArray){
    //read_size = byteArray.size();
     QDataStream stream(&byteArray,QSerialPort::ReadWrite);
    //QDataStream stream(byteArray); //QIODevice:ReadOnly
    stream.setVersion(QDataStream::Qt_4_5);

    stream.startTransaction();
    stream >> retrieve_data;
    stream.commitTransaction();

}
