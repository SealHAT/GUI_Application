#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QTextCursor>
#include <QDebug>

/* Enable/Disable Ekg sensor.
 * Disable all the configuration option if this button is clicked.
*/


void maindialog::setConfigList()
{
    QString xcel_scale = ui->xcel_scaleBox->currentText();
    //ui->xcel_ConfigList->append(xcel_scale);
}
