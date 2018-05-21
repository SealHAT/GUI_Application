#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QTextCursor>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"

/* Enable/Disable Ekg sensor.
 * Disable all the configuration option if this button is clicked.
*/


void maindialog::on_completeButton_clicked()
{
    goto_DEV();
    //mag_dataCollect();
    //qDebug() << "mag mode is 0x:" << QString::number(configuration_settings.magnetometer_config.mag_mode, 16) << endl;
}


void maindialog::setConfigList()
{
    QString xcel_scale = ui->xcel_scaleBox->currentText();
    //ui->xcel_ConfigList->append(xcel_scale);
}
