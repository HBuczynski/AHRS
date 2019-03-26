#include "CallibrationSettings.h"
#include "ui_CallibrationSettings.h"

#include <iostream>

using namespace std;
using namespace peripherals;

CallibrationSettings::CallibrationSettings(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::CallibrationSettings)
{
    ui_->setupUi(this);

    setupPage();
}

CallibrationSettings::~CallibrationSettings()
{
    delete ui_;
}

void CallibrationSettings::setupPage()
{
    this->setStyleSheet("background-color:black;");

    // Title label
    QFont font("Arial", 25, QFont::Bold);
    ui_->titleLabel->setStyleSheet("QLabel { color : white}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("CHOOSE A PLANE");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);

    // PLane Line
    QFont labelFont("Arial", 15, QFont::Bold);
    ui_->planeLabel->setStyleSheet("QLabel { color : white}");
    ui_->planeLabel->setFont(labelFont);
    ui_->planeLabel->setText("CURRENT PLANE");

    ui_->planeDotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->planeDotsLabel->setFont(labelFont);
    ui_->planeDotsLabel->setText("................................................................................................");

    QFont sqareFont("Arial", 22, QFont::Bold);
    ui_->planeValueLabel->setStyleSheet("QLabel { color : white}");
    ui_->planeValueLabel->setFont(sqareFont);
    ui_->planeValueLabel->setText("\u25FB\u25FB\u25FB\u25FB\u25FB\u25FB");

    // Plane from database line
    ui_->fromDatabaseLabel->setStyleSheet("QLabel { color : white}");
    ui_->fromDatabaseLabel->setFont(labelFont);
    ui_->fromDatabaseLabel->setText("FROM DATABASE");

    ui_->fromDatabaseDotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->fromDatabaseDotsLabel->setFont(labelFont);
    ui_->fromDatabaseDotsLabel->setText("................................................................................................");

    ui_->fromDatabaseComboBox->setStyleSheet("background-color: rgb(255,255,255);border: none; ");

    // New plane line
    ui_->newPlaneLabel->setStyleSheet("QLabel { color : white}");
    ui_->newPlaneLabel->setFont(labelFont);
    ui_->newPlaneLabel->setText("NEW PLANE");

    ui_->newPlaneDotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->newPlaneDotsLabel->setFont(labelFont);
    ui_->newPlaneDotsLabel->setText("................................................................................................");

    QFont newPlaneFont("Arial", 15, QFont::Bold);
    ui_->newPlaneLineEdit->setStyleSheet("background-color: rgb(255,255,255);border: none; ");
    ui_->newPlaneLineEdit->setFont(newPlaneFont);

    // Line Under buttons_
    ui_->dotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel->setFont(labelFont);
    ui_->dotsLabel->setText("................................................................................................"
                           "................................................................................................");

    keyboard_ = make_shared<Keyboard>();
    ui_->gridLayout->addWidget(keyboard_.get());

    // Left button
    QFont buttonFont("Arial", 15, QFont::Bold);
    ui_->leftButton->setStyleSheet("QPushButton { background-color: white; }\n"
                                  "QPushButton:pressed { background-color: grey; }\n");
    ui_->leftButton->setFont(buttonFont);

    // Right button
    ui_->rightButton->setStyleSheet("QPushButton { background-color: white; }\n"
                                   "QPushButton:pressed { background-color: grey; }\n");
    ui_->rightButton->setFont(buttonFont);
}

void CallibrationSettings::setupSlots()
{
    connect( ui_->newPlaneLineEdit, SIGNAL(textEdited()), this, SLOT(lineEditClicked()));
}

void CallibrationSettings::lineEditClicked()
{
    cout << "Lolo" << endl;
}

void CallibrationSettings::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "CANCEL";
    buttonNames[SwitchCode::SECOND_SWITCH] = "\u2B9B DOWN";//"\u21E6";
    buttonNames[SwitchCode::THIRD_SWITCH] = "\u2B99 UP";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "SELECT";//"\u21E8";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&CallibrationSettings::cancelButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&CallibrationSettings::upButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&CallibrationSettings::downButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&CallibrationSettings::selectButton, this);

    initializeButtons(buttonNames, callbackFunctions);
}

void CallibrationSettings::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>(this);
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void CallibrationSettings::cancelButton()
{

}

void CallibrationSettings::upButton()
{

}

void CallibrationSettings::downButton()
{


}

void CallibrationSettings::selectButton()
{

}
