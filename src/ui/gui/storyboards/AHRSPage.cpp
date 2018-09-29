#include "AHRSPage.h"
#include "ui_AHRSPage.h"

AHRSPage::AHRSPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AHRSPage)
{
    ui->setupUi(this);

    setup();
}

AHRSPage::~AHRSPage()
{
    delete ui;
}

void AHRSPage::setup()
{
    widgetPFD_ = new WidgetPFD();

    ui->pfdLayout->addWidget(widgetPFD_);
    widgetTC = new WidgetTC();
    ui->devicesLayout->addWidget(widgetTC);
    widgetVSI = new WidgetVSI();
    ui->devicesLayout->addWidget(widgetVSI);

    QFont upFont("Arial", 10, QFont::Bold);
    QFont downFont("Arial", 13, QFont::Bold);

    ui->upFirst->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui->upFirst->setFont(upFont);
    ui->upFirst->setText("NONE");
    ui->downFirst->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui->downFirst->setFont(downFont);
    ui->downFirst->setText("NONE");

    ui->upGrdSpeed->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui->upGrdSpeed->setFont(upFont);
    ui->upGrdSpeed->setText("GRD SPEED");
    ui->downGrdSpeed->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui->downGrdSpeed->setFont(downFont);
    ui->downGrdSpeed->setText("0");

    ui->upAltGps->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui->upAltGps->setFont(upFont);
    ui->upAltGps->setText("ALT (GPS)");
    ui->downAltGps->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui->downAltGps->setFont(downFont);
    ui->downAltGps->setText("0");

    ui->upFltDuration->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui->upFltDuration->setFont(upFont);
    ui->upFltDuration->setText("FLIGHT DURATION");
    ui->downFltDuration->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui->downFltDuration->setFont(downFont);
    ui->downFltDuration->setText("00:00:00");

    ui->upBoxPower->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui->upBoxPower->setFont(upFont);
    ui->upBoxPower->setText("FEEDER POWER");
    ui->downBoxPower->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui->downBoxPower->setFont(downFont);
    ui->downBoxPower->setText("100 %");

    ui->upPowerSupply->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui->upPowerSupply->setFont(upFont);
    ui->upPowerSupply->setText("POWER");
    ui->downPowerSupply->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui->downPowerSupply->setFont(downFont);
    ui->downPowerSupply->setText("100 %");

    buttons = new Buttons();

    ui->buttonLayout->addWidget(buttons);
}
