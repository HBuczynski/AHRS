#include "GpsPage.h"
#include "ui_GpsPage.h"

using namespace std;
using namespace peripherals;

GpsPage::GpsPage(gui::PageController* controller, QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::GpsPage),
    controller_(controller)
{
    ui_->setupUi(this);
    setupPage();
}

GpsPage::~GpsPage()
{
    delete ui_;
}

void GpsPage::setupPage()
{
    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 30, QFont::Bold);
    QFont labelFont("Arial", 20, QFont::Bold);

    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("GPS");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);

    ui_->latitudeLabel->setStyleSheet("QLabel { color : white}");
    ui_->latitudeLabel->setFont(labelFont);
    ui_->latitudeLabel->setText("LATITUDE");

    ui_->dotsLabel_1->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_1->setFont(labelFont);
    ui_->dotsLabel_1->setText("................................................................................................................");

    ui_->latitudeValue->setStyleSheet("QLabel { color : white}");
    ui_->latitudeValue->setFont(labelFont);
    ui_->latitudeValue->setText("0.0");


    ui_->longitudeLabel->setStyleSheet("QLabel { color : white}");
    ui_->longitudeLabel->setFont(labelFont);
    ui_->longitudeLabel->setText("LONGITUDE");

    ui_->dotsLabel_2->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_2->setFont(labelFont);
    ui_->dotsLabel_2->setText(".............................................................................................................................................");

    ui_->longitudeValue->setStyleSheet("QLabel { color : white}");
    ui_->longitudeValue->setFont(labelFont);
    ui_->longitudeValue->setText("0.0000000000");


    ui_->satnumbLabel->setStyleSheet("QLabel { color : white}");
    ui_->satnumbLabel->setFont(labelFont);
    ui_->satnumbLabel->setText("SATTELITE NMB");

    ui_->dotsLabel_3->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_3->setFont(labelFont);
    ui_->dotsLabel_3->setText(".............................................................................................................................................");

    ui_->satnumValue->setStyleSheet("QLabel { color : white}");
    ui_->satnumValue->setFont(labelFont);
    ui_->satnumValue->setText("0.000000");


    ui_->fixLabel->setStyleSheet("QLabel { color : white}");
    ui_->fixLabel->setFont(labelFont);
    ui_->fixLabel->setText("FIX QLT");

    ui_->dotsLabel_4->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_4->setFont(labelFont);
    ui_->dotsLabel_4->setText(".............................................................................................................................................");

    ui_->fixValue->setStyleSheet("QLabel { color : white}");
    ui_->fixValue->setFont(labelFont);
    ui_->fixValue->setText("0.000000");


    ui_->warningLabel->setStyleSheet("QLabel { color : white}");
    ui_->warningLabel->setFont(labelFont);
    ui_->warningLabel->setText("WARNING");

    ui_->dotsLabel_5->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_5->setFont(labelFont);
    ui_->dotsLabel_5->setText(".............................................................................................................................................");

    ui_->warningValue->setStyleSheet("QLabel { color : white}");
    ui_->warningValue->setFont(labelFont);
    ui_->warningValue->setText("0.00000000000");

}

void GpsPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "";
    buttonNames[SwitchCode::SECOND_SWITCH] = "";
    buttonNames[SwitchCode::THIRD_SWITCH] = "";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "< BACK";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&GpsPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&GpsPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&GpsPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&GpsPage::fourthButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalBackPage()), controller_, SLOT(setAHRSPage()));
}

void GpsPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>(this);
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void GpsPage::firstButton()
{

}

void GpsPage::secondButton()
{

}

void GpsPage::thirdButton()
{

}

void GpsPage::fourthButton()
{
    emit signalBackPage();
}
