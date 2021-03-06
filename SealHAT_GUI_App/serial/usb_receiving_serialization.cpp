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
#include "qendian.h"

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
    //QObject::connect(microSerial, SIGNAL(readyRead()), this, SLOT(printData()));

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

    //pos = 0;
    findDataBuffer_fromPacket();

    //pos += sizeof(DATA_HEADER_t);
    recognizeData_fromBuffer();
/*
if(pos){
    for(uint32_t i = pos + sizeof(DATA_HEADER_t);
        i < pos +  sizeof(DATA_HEADER_t) + (header.size/4);
        i++){
        sampleBuf.append(dataBuffer.at(i));
    }
}else{
    qDebug() << "error!";
}*/

    //serialDataBuffer.append(sampleBuf.toHex());


    headerAnalyze_display();

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
    QByteArray pattern_start("\xCA\xFE\xD0\x0D");

    //Now use QByteArrayMatcher to find your byte array.
    QByteArrayMatcher matcherST(pattern_start);
    int begin = 0;
    if((begin = matcherST.indexIn(serial_readData, begin)) != -1) {
        //qDebug() << "pattern begin at" << begin;

        for(uint32_t i = begin + sizeof(uint32_t);
            i < begin + sizeof(uint32_t) + PAGE_SIZE_EXTRA;
            i++)
        {
            dataBuffer.append(serial_readData.at(i));
        }


    }else{
        qDebug() << "No matching start was found";
    }

}

void maindialog::recognizeData_fromBuffer(){
    QByteArray pattern("\xDE\xAD");
    QByteArrayMatcher matcher(pattern);

    //for(pos = pos; pos < pos + (PAGE_SIZE_EXTRA); pos += sizeof(DATA_HEADER_t)){
    //pos += 1;

    pos += sizeof(DATA_HEADER_t);

        if((pos = matcher.indexIn((dataBuffer), pos)) != -1) {
            qDebug() << "dataBuffer found at pos" << pos;
            header_ba.clear();

            for(uint32_t i = pos;
                i < pos + sizeof(DATA_HEADER_t);
                i++)
            {
                header_ba.append((dataBuffer).at(i));
            }
            header_deserialize(header_ba);
            qDebug() << "header size is" << qToBigEndian(header.size);

            serialDataBuffer.clear();
            serialDataBuffer.reserve(qToBigEndian(header.size)*2);
            for(uint64_t i = pos + sizeof(DATA_HEADER_t);
                i < pos +  sizeof(DATA_HEADER_t) + qToBigEndian(header.size);
                i++){
                if(i >= dataBuffer.size()) {
                    qDebug() <<"Too much";
                }

                //sampleBuf.clear();
                //sampleBuf.append(dataBuffer.at(i));
                serialDataBuffer.append(QString::number(dataBuffer.at(i), 16));
            }

    }else{
        qDebug() << "No matching header found";
        }
    //}





}

void maindialog::headerAnalyze_display(){
    uint16_t id = qToBigEndian(header.id);
    qDebug() << "ID is "<<QString::number(id,16);

    switch(id){
    case DEVICE_ID_LIGHT:
        if(ui->light_streamText->toPlainText().size() > 10000) {
            ui->light_streamText->clear();
        }
        ui->light_streamText->moveCursor(QTextCursor::End);
        ui->light_streamText->insertPlainText(serialDataBuffer);
        break;
    case DEVICE_ID_TEMPERATURE:
        if(ui->temp_streamText->toPlainText().size() > 10000) {
            ui->temp_streamText->clear();
        }
        ui->temp_streamText->moveCursor(QTextCursor::End);
        ui->temp_streamText->insertPlainText(serialDataBuffer);
        break;
    case DEVICE_ID_ACCELEROMETER:
                qDebug() << "xcel should displaying";
        if(ui->xcel_streamText->toPlainText().size() > 10000) {
            ui->xcel_streamText->clear();
         }
        ui->xcel_streamText->moveCursor(QTextCursor::End);
        ui->xcel_streamText->insertPlainText(serialDataBuffer);
        break;
    case DEVICE_ID_MAGNETIC_FIELD:
        if(ui->mag_streamText->toPlainText().size() > 10000) {
            ui->mag_streamText->clear();
         }
        ui->mag_streamText->moveCursor(QTextCursor::End);
        ui->mag_streamText->insertPlainText(serialDataBuffer);
        break;

    case DEVICE_ID_GPS:
        if(ui->gps_streamText->toPlainText().size() > 10000) {
            ui->gps_streamText->clear();
         }
        ui->gps_streamText->moveCursor(QTextCursor::End);
        ui->gps_streamText->insertPlainText(serialDataBuffer);
        break;
    case DEVICE_ID_EKG:
        if(ui->ekg_streamText->toPlainText().size() > 10000) {
            ui->ekg_streamText->clear();
         }
        ui->ekg_streamText->moveCursor(QTextCursor::End);
        ui->ekg_streamText->insertPlainText(serialDataBuffer);
        break;
    }

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






