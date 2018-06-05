#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QList>
#include <QMessageBox>
#include <QByteArrayMatcher>
#include <QDataStream>
#include "maindialog.h"
#include "ui_maindialog.h"

/**************************************************************
 * FUNCTION: receiveSerial_samples
 * ------------------------------------------------------------
 * This function gets called when the start streaming button is
 * clicked. Whenever there is data ready signal generated on the
 * serial port.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::receiveSerial_samples()
{
    receive_serialSetup();
    qDebug() << "Serial is trying to receive";
    //connect(microSerial, &QSerialPort::DataTerminalReadySignal, this, &maindialog::serialReceived);
    QObject::connect(microSerial, SIGNAL(readyRead()), this, SLOT(serialReceived()));
}

void maindialog::serialReceived()
{
    serial_readData = microSerial->readAll();
    findDataBuffer_fromPacket(serial_readData);
    //serialDataBuffer =  QString::fromStdString(findDataBuffer_fromPacket(serial_readData).toStdString());

    ui->xcel_streamText->append(serialDataBuffer);

}

void maindialog::findDataBuffer_fromPacket(QByteArray serial_readData){
    QByteArray pattern("ADDE");
    //uint32_t sysPattern = MSG_START_SYM;
    //QByteArray pattern((char*)&sysPattern,1);
    QByteArray buffer;

    //Now use QByteArrayMatcher to find your byte array.
    QByteArrayMatcher matcher(pattern);
    uint32_t pos = 0;
    if((pos = matcher.indexIn(serial_readData, pos)) != -1) {
        qDebug() << "pattern found at pos" << pos;
        for(uint32_t i = pos + sizeof(uint32_t);
            i < pos + sizeof(uint32_t) + PAGE_SIZE_EXTRA;
            i++)
        {
            //buffer.append(serial_readData.at(i));
            serialDataBuffer.append(serial_readData.at(i));
        }
    }
}

void maindialog::recognizeData_fromBuffer(QByteArray buffer){
    //QByteArray pattern("ADDE"); //Header patter
    data_deserialize(buffer);
    searchingHeader();

    //uin8_t* buffer = buffer;

    //Now use QByteArrayMatcher to find your byte array.
    /*QByteArrayMatcher matcher(pattern);
    uint32_t pos = 0;
    if((pos = matcher.indexIn(buffer, pos)) != -1) {

    }*/
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
    case DEVICE_ID_TEMPERATURE:
        for(int i = 0; i < (header->size/4); i++){
            ui->temp_streamText->append(QString(((uint32_t*)data_startPoint)[i]));
        }
        break;
    case DEVICE_ID_ACCELEROMETER:
        for(int i = 0; i < (header->size/4); i++){
            ui->xcel_streamText->append(QString(((uint32_t*)data_startPoint)[i]));
        }
        break;
    case DEVICE_ID_MAGNETIC_FIELD:
        for(int i = 0; i < (header->size/4); i++){
            ui->mag_streamText->append(QString(((uint32_t*)data_startPoint)[i]));
        }
        break;

    case DEVICE_ID_GPS:
        for(int i = 0; i < (header->size/4); i++){
            ui->gps_streamText->append(QString(((uint32_t*)data_startPoint)[i]));
        }
        break;
    case DEVICE_ID_EKG:
        for(int i = 0; i < (header->size/4); i++){
            ui->ekg_streamText->append(QString(((uint32_t*)data_startPoint)[i]));
        }
        break;


    }

}



QDataStream& operator>>(QDataStream& stream, DATA_TRANSMISSION_t& txData) {

    for(int i=0;i<PAGE_SIZE_EXTRA; i++){
        stream >> txData.data[i];
    }

    return stream;
}


void maindialog::data_deserialize(QByteArray& byteArray){

    //QDataStream stream(&byteArray,QSerialPort::ReadWrite);
    QDataStream stream(byteArray);
    stream.setVersion(QDataStream::Qt_4_5);

    //stream.startTransaction();
    stream >> retrieve_data;
    //stream.commitTransaction();

}



