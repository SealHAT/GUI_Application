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
    QObject::connect(microSerial, SIGNAL(readyRead()), this, SLOT(serialReceived()));
}


/**************************************************************
 * FUNCTION: serialReceived
 * ------------------------------------------------------------
 * This function will be called whenever there is data ready
 * signal generated on the serial port from microcontroller side.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::serialReceived()
{
    serial_readData = microSerial->readAll();
    findDataBuffer_fromPacket();



    ui->xcel_streamText->append(serialDataBuffer);
    //serialDataBuffer =  QString::fromStdString(findDataBuffer_fromPacket(serial_readData).toStdString());



}


/**************************************************************
 * FUNCTION: findDataBuffer_fromPacket
 * ------------------------------------------------------------
 * This function will be called whenever there is data ready
 * signal generated on the serial port from microcontroller side.
 *
 *  Parameters: none
 *
 *  Returns: void
 **************************************************************/
void maindialog::findDataBuffer_fromPacket(){
    QByteArray pattern("\xDE\xAD");
    //QByteArray patternHex {0xDE,0xAD};

    QByteArray dataBuffer;

    //Now use QByteArrayMatcher to find your byte array.
    QByteArrayMatcher matcher(pattern);
    int pos = 0;
    if((pos = matcher.indexIn(serial_readData, pos)) != -1) {
        qDebug() << "pattern found at pos" << pos;
        for(uint32_t i = pos + sizeof(uint32_t);
            i < pos + sizeof(uint32_t) + PAGE_SIZE_EXTRA;
            i++)
        {
            dataBuffer.append(serial_readData.at(i));
            //serialDataBuffer.append(QString::number(static_cast<unsigned char>(serial_readData[i]), 16).toUpper());
            serialDataBuffer.append(dataBuffer.toHex());
        }
        recognizeData_fromBuffer(dataBuffer);

    }else{
        qDebug() << "No matching was found";
    }

}

void maindialog::recognizeData_fromBuffer(QByteArray databuffer){
    //QByteArray patternHex(MSG_START_SYM,1);
    QByteArray pattern("\xDE\xAD");
    QByteArrayMatcher matcher(pattern);

    int pos = 0;
    if((pos = matcher.indexIn(databuffer, pos)) != -1) {
        qDebug() << "dataBuffer found at pos" << pos;
        QByteArray header_ba;

        for(uint32_t i = pos;
            i < pos + sizeof(DATA_HEADER_t);
            i++)
        {
            header_ba.append(serial_readData.at(i));
        }

        header_deserialize(header_ba);
        qDebug() << header.startSym;
        qDebug() << header.id;

    }

}

QDataStream& operator>>(QDataStream& stream, DATA_HEADER_t& data_header) {
    quint32 temp_timestamp;
    quint16 temp_startSym, temp_id, temp_msTime, temp_size;

    stream >> temp_startSym
           >> temp_id
           >> temp_timestamp
           >> temp_msTime
           >> temp_size;

    data_header.startSym  = (uint16_t)temp_startSym;
    data_header.id        = (uint16_t)temp_id;
    data_header.timestamp = (uint32_t)temp_timestamp;
    data_header.msTime    = (uint16_t)temp_msTime;
    data_header.size    = (uint16_t)temp_size;

    return stream;
}

void maindialog::header_deserialize(QByteArray& byteArray){
    //DATA_HEADER_t header;

    QDataStream stream(&byteArray,QSerialPort::ReadWrite);
    stream.setVersion(QDataStream::Qt_4_5);

    //stream.startTransaction();
    stream >> header;

    //return header;
    //stream.commitTransaction();
}




void maindialog::searchingHeader(){

    DATA_HEADER_t* firstSampleHeader = (DATA_HEADER_t*)retrieve_data.data;

    for(DATA_HEADER_t* curr = firstSampleHeader;
        curr+sizeof(DATA_HEADER_t)+curr->size < firstSampleHeader+PAGE_SIZE_EXTRA;
        curr += (sizeof(DATA_HEADER_t) + curr->size)) {
        recognizeData(curr);
    }
}

void maindialog::recognizeData(DATA_HEADER_t *header){
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
    quint32 temp_startSymbol;
    quint32 temp_crc;

    stream >> temp_startSymbol;

    for(int i=0;i<PAGE_SIZE_EXTRA; i++){
        stream >> txData.data[i];
    }

    stream >> temp_crc;

    txData.startSymbol = (uint32_t)temp_startSymbol;
    txData.crc = (uint32_t)temp_crc;

    return stream;
}


void maindialog::data_deserialize(QByteArray& byteArray){

    QDataStream stream(&byteArray,QSerialPort::ReadWrite);
    stream.setVersion(QDataStream::Qt_4_5);

    //stream.startTransaction();
    stream >> retrieve_data;
    //stream.commitTransaction();

}






