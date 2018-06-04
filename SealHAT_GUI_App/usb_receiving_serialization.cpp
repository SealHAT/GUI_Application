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
    qDebug() << "Serial is trying to receive";
    if(microSerial->DataTerminalReadySignal){
        serial_readData = microSerial->readAll();
        serialBuffer = QString::fromStdString(serial_readData.toStdString());
        ui->xcelStreamText->append(serialBuffer);
    }
    //connect(microSerial, &QSerialPort::DataTerminalReadySignal, this, &maindialog::serialReceived);
    QObject::connect(microSerial, SIGNAL(readyRead()), this, SLOT(serialReceived()));
}

void maindialog::serialReceived()
{
    serial_readData = microSerial->readAll();
    //data_deserialize(serial_readData);

    //retrieve_data.data ==

    serialBuffer = QString::fromStdString(serial_readData.toStdString());
    ui->xcelStreamText->append(serialBuffer);
    //ui->serialLabel->setText(serial_readData);
    //qDebug() << serialBuffer;
    qDebug() << "Serial is working";
}


void maindialog::recognizeData(DATA_HEADER_t *header){
    //((DATA_HEADER_t*)data)->size
    //*(DATA_HEADER_t*)(data+sizeof(DATA_HEADER_t)+(*(DATA_HEADER_t*)data).size)
    //uint16_t sample_size[200];
    uint16_t id = (header->id);

    uint8_t* data_startPoint = (uint8_t*)(header+sizeof(DATA_HEADER_t));

    switch(id){
    case DEVICE_ID_LIGHT:
        for(int i = 0; i < (header->size/4); i++){
            ui->light_streamText->append(QString(((uint32_t*)data_startPoint)[i]));
        }
        break;


    }

}

void maindialog::searchingHeader(){
    DATA_HEADER_t* firstSampleHeader = (DATA_HEADER_t*)retrieve_data.data;
    //recognizeData();
    for(DATA_HEADER_t* curr = firstSampleHeader;
        curr+sizeof(DATA_HEADER_t)+curr->size < firstSampleHeader+PAGE_SIZE_EXTRA;
        curr += (sizeof(DATA_HEADER_t) + curr->size)) {
        recognizeData(curr);
    }
}

QDataStream& operator>>(QDataStream& stream, DATA_TRANSMISSION_t& txData) {

    quint32 temp_startSymbol;
    quint32 temp_crc;

    stream >> temp_startSymbol;

    for(int i=0;i<PAGE_SIZE_EXTRA; i++){
        stream >> txData.data[i];
    }

    stream >> temp_crc;

    txData.startSymbol = temp_startSymbol;
    txData.crc = temp_crc;

    return stream;
}


void maindialog::data_deserialize(QByteArray& byteArray){

    QDataStream stream(&byteArray,QSerialPort::ReadWrite);
    stream.setVersion(QDataStream::Qt_4_5);

    stream.startTransaction();
    stream >> retrieve_data;
    stream.commitTransaction();

}



