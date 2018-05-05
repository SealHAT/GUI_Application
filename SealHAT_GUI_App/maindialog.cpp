#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDesktopWidget>
#include <QMessageBox>

#include <QDebug>

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

    connect( ui->b, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_2, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_3, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_4, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_5, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_6, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_7, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_8, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_9, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_10, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_11, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_12, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_13, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_14, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_15, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_16, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_17, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_18, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_19, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_20, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_21, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_22, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_23, SIGNAL(clicked()), this, SLOT(hour_clicked()));
    connect( ui->b_24, SIGNAL(clicked()), this, SLOT(hour_clicked()));

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


void maindialog::hour_clicked()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!button->property("clicked").isValid()) {
        button->setProperty("clicked", false);
    }
    bool clicked = button->property("clicked").toBool();
    button->setProperty("clicked", !clicked);

    if(!clicked) {
        button->setStyleSheet("background-color:rgb(34,139,34)");
        temporaryTemp.temp_time |= 1 << button->property("button_shift").toInt();
    } else {
        button->setStyleSheet("background-color:rgb(152, 162, 173)");
        temporaryTemp.temp_time &= ~(1 << button->property("button_shift").toInt());
    }
    qDebug() << "time is :" << temporaryTemp.temp_time << endl;
}
