#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>

#include <QDebug>
bool sw = true;
/**
 * Initial GUI setup.
 **/
maindialog::maindialog(QWidget *parent) : QDialog(parent), ui(new Ui::maindialog)
{
    ui->setupUi(this);

    // On the Login stack, set the welcome page.
    ui->StartPageStacked->setCurrentIndex(INITIAL_PAGE);

    // Set size for smaller welcome screen.
    this->setFixedSize(421, 421);

    // Hide all the warning label on the IMU page
    ui->thres_warnLABEL->hide();
    ui->dur_warnLABEL->hide();
}

/**
 * Delete GUI on exit.
 **/
maindialog::~maindialog()
{
    delete ui;
}

void maindialog::on_configureDevOptionButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(1);
    ui->ConfigurePages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
    this->centerDialog();
}

void maindialog::on_retrieveDataButton_clicked()
{
    this->setFixedSize(850, 558);

    ui->mainStacked->setCurrentIndex(2);
    ui->ConfigurePages->setCurrentIndex(RETRIEVE_DATA_HOME_PAGE);
    this->centerDialog();
}

/**
 * Center the contents of the page.
 **/
void maindialog::centerDialog() {
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}



void maindialog::on_b_23_clicked()
{
    if(sw == true){
        ui->b_23->setStyleSheet("background-color:rgb(34,139,34)");
        sw = false;

    }else{
        ui->b_23->setStyleSheet("background-color:rgb(152, 162, 173)");
        sw = true;
    }

}

/*void maindialog::on_b_23_clicked(bool checked)
{
    if(checked == true){
        ui->b_23->setStyleSheet("background-color:rgb(34,139,34)");
        //sw -= 1;

    }else{
        ui->b_23->setStyleSheet("background-color:rgb(152, 162, 173)");
    }
}*/

void maindialog::on_b_clicked()
{

}

void maindialog::on_b_toggled(bool checked)
{
    if(checked == true){
        ui->b->setStyleSheet("background-color:rgb(34,139,34)");
        //checked = false;

    }else{
        ui->b->setStyleSheet("background-color:rgb(152, 162, 173)");
        //checked = true;
    }

}

void maindialog::on_b_clicked(bool checked)
{

}
