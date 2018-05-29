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
    serialSetup();
    serialReceived();
    //retrieve_data;
}

void maindialog::serialReceived()
{
    serial_readData = microSerial->readAll();
    serialBuffer = QString::fromStdString(serial_readData.toStdString());
    ui->serialLabel->setText(serial_readData);
    //qDebug() << serialBuffer;
    //qDebug() << "Serial is working";
}

