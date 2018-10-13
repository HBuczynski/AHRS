#include "ConnectingPage.h"
#include "ui_ConnectingPage.h"

ConnectingPage::ConnectingPage(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::ConnectingPage)
{
    ui_->setupUi(this);
    setupPage();
}

ConnectingPage::~ConnectingPage()
{
    delete ui_;
}

void ConnectingPage::setupPage()
{
    // Title label
    QFont font("Arial", 25, QFont::Bold);
    this->setStyleSheet("background-color:black;");

    ui_->connectingLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->connectingLabel->setFont(font);
    ui_->connectingLabel->setText("CONNECTING TO FEEDER ...");
    ui_->connectingLabel->setAlignment(Qt::AlignCenter);

    QFont fontSub("Arial", 14, QFont::Bold);
    ui_->subTextLabel->setStyleSheet("QLabel { color: white}");
    ui_->subTextLabel->setFont(fontSub);
    ui_->subTextLabel->setText("Check whether feeder device is switched on.");
    ui_->subTextLabel->setAlignment(Qt::AlignCenter);
}
