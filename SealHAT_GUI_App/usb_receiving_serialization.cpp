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

    //retrieve_data.data ==

    //serialBuffer = QString::fromStdString(retrieve_data.toStdString());
    ui->xcelStreamText->setText(serialBuffer);
    //ui->serialLabel->setText(serial_readData);
    //qDebug() << serialBuffer;
    qDebug() << "Serial is working";
}

/*
void maindialog::recognizeData(){
    retrieve_data.data
}*/

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



